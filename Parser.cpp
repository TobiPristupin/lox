#include <iostream>
#include "Parser.h"
#include "TokenType.h"
#include "LoxError.h"
#include "Expr.h"
#include "gsl/gsl"

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens) {}

std::vector<UniqueStmtPtr> Parser::parse(bool &successFlag) {
    successFlag = true;
    std::vector<UniqueStmtPtr> statements;
    while (!isAtEnd()){
        UniqueStmtPtr stmt = declaration();
        statements.push_back(std::move(stmt));
    }

    successFlag = !hadError;
    return statements;
}

//If a parsing error is encountered, this function will attempt to synchronize the parser and then return nullptr.
UniqueStmtPtr Parser::declaration() {
    try {
        if (match(TokenType::VAR)) return varDeclStatement();
        if (match(TokenType::FUN)) return functionDeclStatement(FunctionType::FUNCTION);
        return statement();
    } catch (const LoxParsingError &error) {
        //Report the exception but don't let it bubble up and stop the program. Instead, synchronize the parser and keep parsing.
        std::cout << error.what() << "\n";
        hadError = true;
        synchronize();
    }

    return nullptr;
}

UniqueStmtPtr Parser::varDeclStatement() {
    Token identifier = expect(TokenType::IDENTIFIER, "Expected identifier");
    UniqueExprPtr initializer = nullptr;
    if (match(TokenType::EQUAL)){
        initializer = expression();
    }

    expect(TokenType::SEMICOLON, "Expect ';' after variable declaration");
    return std::make_unique<VarDeclarationStmt>(identifier, std::move(initializer));
}

UniqueStmtPtr Parser::functionDeclStatement(FunctionType type) {
    std::string type_str = type == FunctionType::FUNCTION ? "function" : "method";
    Token name = expect(TokenType::IDENTIFIER, "Expected " + type_str + " name");
    expect(TokenType::LEFT_PAREN, "Expected '(' after " + type_str + " name");

    std::vector<Token> parameters;
    if (!check(TokenType::RIGHT_PAREN)){
        do {
            if (parameters.size() >= 255){
                //Report the error but don't throw it bc throwing it will cause the parser to synchronize and we want to keep parsing
                std::cout << error(type_str + " cannot have more than 255 parameters", peek().line).what() << "\n";
                hadError = true;
            }
            Token param = expect(TokenType::IDENTIFIER, "Expected parameters name");
            parameters.push_back(param);
        } while (match(TokenType::COMMA));
    }

    expect(TokenType::RIGHT_PAREN, "Expected ')' after parameter list");
    expect(TokenType::LEFT_BRACE, "Expected '{' before " + type_str + " body");

    std::vector<UniqueStmtPtr> body = block();
    return std::make_unique<FunctionDeclStmt>(name, parameters, std::move(body));
}

UniqueStmtPtr Parser::statement() {
    if (match(TokenType::PRINT)) return printStatement();
    if (match(TokenType::LEFT_BRACE)) return std::make_unique<BlockStmt>(block());
    if (match(TokenType::IF)) return ifStatement();
    if (match(TokenType::WHILE)) return whileStatement();
    if (match(TokenType::FOR)) return forStatement();
    if (match(TokenType::BREAK)) return breakStatement();
    if (match(TokenType::CONTINUE)) return continueStatement();
    if (match(TokenType::RETURN)) return returnStatement();

    return exprStatement();
}

std::vector<UniqueStmtPtr> Parser::block() {
    std::vector<UniqueStmtPtr> statements;
    while (!isAtEnd() && !check(TokenType::RIGHT_BRACE)){
        UniqueStmtPtr stmt = declaration();
        statements.push_back(std::move(stmt));
    }

    expect(TokenType::RIGHT_BRACE, "Expected } after block");
    return statements;
}

UniqueStmtPtr Parser::exprStatement() {
    UniqueExprPtr expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after value.");
    return std::make_unique<ExpressionStmt>(std::move(expr));
}

UniqueStmtPtr Parser::printStatement() {
    if (match(TokenType::SEMICOLON)){
        return std::make_unique<PrintStmt>(nullptr);
    }

    UniqueExprPtr expr = expression();
    expect(TokenType::SEMICOLON, "Expect ';' after expression.");
    return std::make_unique<PrintStmt>(std::move(expr));
}

UniqueStmtPtr Parser::ifStatement() {
    expect(TokenType::LEFT_PAREN, "Expect '(' after if");
    UniqueExprPtr condition = expression();
    expect(TokenType::RIGHT_PAREN, "Expect ')' after if condition");
    UniqueStmtPtr thenStmt = statement();
    IfBranch mainBranch(std::move(condition), std::move(thenStmt));


    std::vector<IfBranch> elifBranches;
    while (match(TokenType::ELIF)){
        expect(TokenType::LEFT_PAREN, "Expect '(' after elif");
        UniqueExprPtr elifCondition = expression();
        expect(TokenType::RIGHT_PAREN, "Expect ')' after elif condition");
        UniqueStmtPtr elifStmt = statement();
        IfBranch elifBranch(std::move(elifCondition), std::move(elifStmt));
        elifBranches.push_back(std::move(elifBranch));
    }


    UniqueStmtPtr elseStmt = nullptr;
    if (match(TokenType::ELSE)){
        elseStmt = statement();
    }

    return std::make_unique<IfStmt>(std::move(mainBranch), std::move(elifBranches), std::move(elseStmt));
}

UniqueStmtPtr Parser::whileStatement() {
    loopNestingLevel++;
    auto finalAction = gsl::finally([this] {this->loopNestingLevel--;}); //Make sure that loopNestingLevel is decreased even if exceptions are thrown
    expect(TokenType::LEFT_PAREN, "Expect '(' after while");
    UniqueExprPtr condition = expression();
    expect(TokenType::RIGHT_PAREN, "Expect ')' after while condition");
    UniqueStmtPtr body = statement();
    return std::make_unique<WhileStmt>(std::move(condition), std::move(body));
}

UniqueStmtPtr Parser::forStatement() {
    loopNestingLevel++;
    auto finalAction = gsl::finally([this] {this->loopNestingLevel--;}); //Make sure that loopNestingLevel is decreased even if exceptions are thrown
    expect(TokenType::LEFT_PAREN, "Expect '(' after for");
    UniqueStmtPtr initializer = nullptr;
    if (match(TokenType::VAR)){
        initializer = varDeclStatement();
    } else if (match(TokenType::SEMICOLON)){
        initializer = nullptr;
    } else {
        initializer = exprStatement();
    }

    UniqueExprPtr condition = nullptr;
    if (!check(TokenType::SEMICOLON)){
        condition = expression();
    }
    expect(TokenType::SEMICOLON, "Expect ';' after condition");

    UniqueStmtPtr increment = nullptr;
    if (!check(TokenType::RIGHT_PAREN)){
        increment = std::make_unique<ExpressionStmt>(expression());
    }

    expect(TokenType::RIGHT_PAREN, "Expect ')' after for");
    UniqueStmtPtr body = statement();
    return std::make_unique<ForStmt>(std::move(initializer), std::move(condition), std::move(increment), std::move(body));
}

UniqueStmtPtr Parser::breakStatement() {
    expect(TokenType::SEMICOLON, "Expect ';' after break");
    if (loopNestingLevel == 0){
        throw error("break statement must be inside of a loop", previous().line);
    }
    return std::make_unique<BreakStmt>();
}

UniqueStmtPtr Parser::continueStatement() {
    expect(TokenType::SEMICOLON, "Expect ';' after continue");
    if (loopNestingLevel == 0){
        throw error("continue statement must be inside of a loop", previous().line);
    }
    return std::make_unique<ContinueStmt>();
}

UniqueStmtPtr Parser::returnStatement() {
    Token keyword = previous();
    UniqueExprPtr expr = nullptr;
    if (!check(TokenType::SEMICOLON)){
        expr = expression();
    }

    expect(TokenType::SEMICOLON, "Expected ';' after return statement");
    return std::make_unique<ReturnStmt>(keyword, std::move(expr));
}


UniqueExprPtr Parser::expression() {
    return assignment();
}

UniqueExprPtr Parser::assignment() {
    UniqueExprPtr expr = lambda();
    if (match(EQUAL)){
        Token op = previous();
        UniqueExprPtr rvalue = assignment();
        VariableExpr* lvalue = dynamic_cast<VariableExpr*>(expr.get());

        if (lvalue){
            Token identifier = lvalue->identifier;
            return std::make_unique<AssignmentExpr>(identifier, std::move(rvalue));
        }

        throw error("Invalid assignment target", op.line);
    }

    return expr;
}

UniqueExprPtr Parser::lambda() {
    if (!match(TokenType::LAMBDA)){
        return logicOr();
    }

    std::vector<Token> params;
    if (!check(TokenType::COLON)){
        do {
            if (params.size() >= 255){
                //Report the error but don't throw it bc throwing it will cause the parser to synchronize and we want to keep parsing
                std::cout << error("Lambda expression cannot have more than 255 parameters", peek().line).what() << "\n";
                hadError = true;
            }

            Token param = expect(TokenType::IDENTIFIER, "Expected parameter for lambda expression");
            params.push_back(param);
        } while (match(TokenType::COMMA));
    }
    expect(TokenType::COLON, "Expected colon after lambda parameter list");
//    UniqueStmtPtr body = statement();
    UniqueExprPtr body = logicOr();
    return std::make_unique<LambdaExpr>(params, std::move(body));
}

UniqueExprPtr Parser::logicOr() {
    UniqueExprPtr expr = logicAnd();
    while (match(TokenType::OR)){
        UniqueExprPtr right = logicAnd();
        expr = std::make_unique<OrExpr>(std::move(expr), std::move(right));
    }

    return expr;
}

UniqueExprPtr Parser::logicAnd() {
    UniqueExprPtr expr = equality();
    while (match(TokenType::AND)){
        UniqueExprPtr right = equality();
        expr = std::make_unique<AndExpr>(std::move(expr), std::move(right));
    }

    return expr;
}

UniqueExprPtr Parser::equality() {
    UniqueExprPtr expr = comparison();
    std::vector<TokenType> equalityTokens = {TokenType ::EQUAL_EQUAL, TokenType::BANG_EQUAL};
    while (match(equalityTokens)){
        Token op = previous();
        UniqueExprPtr right = comparison();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::comparison() {
    UniqueExprPtr expr = addition();
    std::vector<TokenType> comparisonTokens = {TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL};
    while (match(comparisonTokens)){
        Token op = previous();
        UniqueExprPtr right = addition();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::addition() {
    UniqueExprPtr expr = multiplication();
    std::vector<TokenType> additionTokens = {TokenType::MINUS, TokenType::PLUS};
    while (match(additionTokens)){
        Token op = previous();
        UniqueExprPtr right = multiplication();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;

}

UniqueExprPtr Parser::multiplication() {
    UniqueExprPtr expr = unary();
    std::vector<TokenType> multiplicationTokens = {TokenType::SLASH, TokenType::STAR};
    while (match(multiplicationTokens)){
        Token op = previous();
        UniqueExprPtr right = unary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), op);
    }

    return expr;
}

UniqueExprPtr Parser::unary() {
    std::vector<TokenType> unaryTokens = {TokenType::MINUS, TokenType::BANG};
    if (match(unaryTokens)){
        Token op = previous();
        UniqueExprPtr right = unary();
        return std::make_unique<UnaryExpr>(op, std::move(right));
    }

    return prefix();
}

UniqueExprPtr Parser::prefix() {
    std::vector<TokenType> prefixTokens = {TokenType::PLUS_PLUS, TokenType::MINUS_MINUS};
    if (match(prefixTokens)){
        Token op = previous();
        UniqueExprPtr right = prefix();
        if (dynamic_cast<IncrementExpr*>(right.get()) || dynamic_cast<DecrementExpr*>(right.get())){
            throw error("Operators '++' and '--' cannot be concatenated", peek().line);
        }

        VariableExpr* lvalue = dynamic_cast<VariableExpr*>(right.get());
        if (lvalue){
            Token identifier = lvalue->identifier;
            if (op.type == TokenType::PLUS_PLUS) return std::make_unique<IncrementExpr>(identifier, IncrementExpr::Type::PREFIX);
            else return std::make_unique<DecrementExpr>(identifier, DecrementExpr::Type::PREFIX);
        } else {
            throw error("Operators '++' and '--' must be applied to an lvalue operand (a variable)", op.line);
        }
    }

    return postfix();
}

UniqueExprPtr Parser::postfix() {
    UniqueExprPtr expr = functionCall();
    std::vector<TokenType> postfixTokens = {TokenType::PLUS_PLUS, TokenType::MINUS_MINUS};
    if (match(postfixTokens)){
        Token op = previous();
        VariableExpr* lvalue = dynamic_cast<VariableExpr*>(expr.get());
        if (lvalue){
            Token identifier = lvalue->identifier;
            if (op.type == TokenType::PLUS_PLUS) expr = std::make_unique<IncrementExpr>(identifier, IncrementExpr::Type::POSTFIX);
            else expr = std::make_unique<DecrementExpr>(identifier, DecrementExpr::Type::POSTFIX);
        } else {
            throw error("Operators '++' and '--' must be applied to an lvalue operand (a variable)", op.line);
        }
    }

    if (match(postfixTokens)){
        throw error("Operators '++' and '--' cannot be concatenated", peek().line);
    }

    return expr;
}

UniqueExprPtr Parser::functionCall() {
    UniqueExprPtr expr = primary();
    while (true){
        if (match(TokenType::LEFT_PAREN)){
            expr = finishCall(std::move(expr));
        } else {
            break;
        }
    }

    return expr;
}

UniqueExprPtr Parser::finishCall(UniqueExprPtr expr) {
    std::vector<UniqueExprPtr> arguments;
    if (!check(TokenType::RIGHT_PAREN)){
        do {
            if (arguments.size() >= 255){
                //Report the error but don't throw it bc throwing it will cause the parser to synchronize and we want to keep parsing
                std::cout << error("Cannot have more than 255 arguments", peek().line).what() << "\n";
                hadError = true;
            }

            UniqueExprPtr parameter = expression();
            arguments.push_back(std::move(parameter));
        } while (match(TokenType::COMMA));
    }

    Token closingParen = expect(TokenType::RIGHT_PAREN, "Expect closing parenthesis after function argument list");
    return std::make_unique<FunctionCallExpr>(std::move(expr), closingParen, std::move(arguments));
}

UniqueExprPtr Parser::primary() {
    if (match(TokenType::NUMBER)) return std::make_unique<LiteralExpr>(LoxObject(previous()));
    if (match(TokenType::STRING)) return std::make_unique<LiteralExpr>(LoxObject(previous()));
    if (match(TokenType::TRUE)) return std::make_unique<LiteralExpr>(LoxObject(previous()));
    if (match(TokenType::FALSE)) return std::make_unique<LiteralExpr>(LoxObject(previous()));
    if (match(TokenType::NIL)) return std::make_unique<LiteralExpr>(LoxObject(previous()));
    if (match(TokenType::IDENTIFIER)) return std::make_unique<VariableExpr>(previous());


    if (match(TokenType::LEFT_PAREN)){
        UniqueExprPtr expr = expression();
        expect(TokenType::RIGHT_PAREN, "Expect ')' after expression");
        return std::make_unique<GroupingExpr>(std::move(expr));
    }


    throw error("Expected expression", peek().line);
}

bool Parser::match(const TokenType &type) {
    std::vector<TokenType> vec = {type};
    return match(vec);
}

//Checks if the current token type matches one from types AND CONSUMES IT
bool Parser::match(const std::vector<TokenType> &types) {
    for (const TokenType &type : types){
        if (check(type)){
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::check(const TokenType &type) {
    if (isAtEnd()) return false;
    return peek().type == type;
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current-1];
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::isAtEnd() {
    return peek().type == TokenType::END_OF_FILE;
}

//checks if the next token is what's expected. Throws an error if it isn't, returns it if it is.
Token Parser::expect(const TokenType &type, const std::string &error_message){
    if (check(type)) return advance();
    else throw error(error_message, peek().line);
}

LoxParsingError Parser::error(const std::string &message, int line) {
    return LoxParsingError(message, line);
}

void Parser::synchronize() { //synchronizes the parser to the next statement when it finds an error
    while (!isAtEnd()){
        if (previous().type == TokenType::SEMICOLON){
            return; //found new statement
        }

        switch (peek().type) {
            case CLASS:
            case FUN:
            case VAR:
            case FOR:
            case IF:
            case WHILE:
            case PRINT:
            case RETURN:
                return; //found new statement;
        }

        advance(); //keep advancing until finding a new statement

    }

}





