#include <iostream>
#include <gsl/gsl_util>
#include "Resolver.h"
#include "LoxError.h"


std::unordered_map<const Expr*, int> Resolver::resolve(const std::vector<UniqueStmtPtr> &stmts, bool &successFlag) {
    successFlag = true;
    for (auto const &stmt : stmts){
        try {
            resolve(stmt.get());
        } catch (const LoxParsingError &error) {
            std::cout << error.what() << "\n";
            successFlag = false;
        }
    }

    return distances;
}

void Resolver::resolve(const std::vector<UniqueStmtPtr> &stmts) {
    for (auto const &stmt : stmts){
        resolve(stmt.get());
    }
}

void Resolver::resolve(Stmt *stmt) {
    stmt->accept(*this);
}

void Resolver::resolve(Expr *expr) {
    expr->accept(*this);
}

void Resolver::resolveLocal(const Expr *expr, const Token &name) {
    for (int i = scopes.size() - 1; i >= 0; i--){
        if (scopes[i].find(name.lexeme) != scopes[i].end()){
            distances[expr] = scopes.size() - i - 1; //number of hops when resolving variable
            return;
        }
    }

    //If it is not found we assume the variable was global
}

void Resolver::beginScope() {
    scopes.emplace_back(std::unordered_map<std::string, bool>());
}

void Resolver::endScope() {
    scopes.pop_back();
}

void Resolver::declare(const Token &name) {
    if (scopes.empty()){
        return;
    }

    if (scopes.back().find(name.lexeme) != scopes.back().end()){
        throw LoxParsingError("Cannot redefine a variable. Variable '" + name.lexeme + "' has already been defined.", name.line);
    }

    scopes.back()[name.lexeme] = false;
}

void Resolver::define(const Token &name) {
    if (scopes.empty()){
        return;
    }

    scopes.back()[name.lexeme] = true;
}

void Resolver::visit(const ExpressionStmt *expressionStmt) {
    resolve(expressionStmt->expr.get());
}

void Resolver::visit(const PrintStmt *printStmt) {
    resolve(printStmt->expr.get());
}

void Resolver::visit(const VarDeclarationStmt *varStmt) {
    declare(varStmt->identifier);
    if (varStmt->expr != nullptr){
        resolve(varStmt->expr.get());
    }
    define(varStmt->identifier);
}

void Resolver::visit(const BlockStmt *blockStmt) {
    beginScope();
    resolve(blockStmt->statements);
    endScope();
}

void Resolver::visit(const IfStmt *ifStmt) {
    resolve(ifStmt->mainBranch.condition.get());
    resolve(ifStmt->mainBranch.statement.get());
    for (const IfBranch &branch : ifStmt->elifBranches){
        resolve(branch.condition.get());
        resolve(branch.statement.get());
    }

    if (ifStmt->elseBranch != nullptr){
        resolve(ifStmt->elseBranch.get());
    }
}

void Resolver::visit(const WhileStmt *whileStmt) {
    loopNestingLevel++;

    auto finalAction = gsl::finally([this] {this->loopNestingLevel--;}); //Make sure that loopNestingLevel is decreased even if exceptions are thrown
    resolve(whileStmt->condition.get());
    resolve(whileStmt->body.get());
}

void Resolver::visit(const BreakStmt *breakStmt) {
    if (loopNestingLevel == 0){
        throw LoxParsingError("'break' statement must be inside of a loop", breakStmt->keyword.line);
    }
}

void Resolver::visit(const ContinueStmt *continueStmt) {
    if (loopNestingLevel == 0){
        throw LoxParsingError("'continue' statement must be inside of a loop", continueStmt->keyword.line);
    }
}

void Resolver::visit(const ForStmt *forStmt) {
    loopNestingLevel++;
    auto finalAction = gsl::finally([this] {this->loopNestingLevel--;});

    beginScope();
    if (forStmt->initializer.get() != nullptr) resolve(forStmt->initializer.get());
    if (forStmt->condition.get() != nullptr) resolve(forStmt->condition.get());
    if (forStmt->increment.get() != nullptr) resolve(forStmt->increment.get());
    resolve(forStmt->body.get());
    endScope();
}

void Resolver::visit(const FunctionDeclStmt *functionStmt) {
    declare(functionStmt->name);
    define(functionStmt->name);
    resolveFunction(functionStmt, FunctionType::FUNCTION);
}

void Resolver::resolveFunction(const FunctionDeclStmt *functionStmt, FunctionType type) {
    FunctionType enclosing = currentFunction;
    currentFunction = type;
    auto finalAction = gsl::finally([this, enclosing] {this->currentFunction = enclosing;});

    beginScope();
    for (const Token &param : functionStmt->params){
        declare(param);
        define(param);
    }

    resolve(functionStmt->body);
    endScope();

}

void Resolver::visit(const ClassDeclStmt *classDeclStmt) {
    declare(classDeclStmt->identifier);
    define(classDeclStmt->identifier);
}

void Resolver::visit(const ReturnStmt *returnStmt) {
    if (currentFunction == FunctionType::NONE){
        throw LoxParsingError("'return' statement must be inside a function", returnStmt->keyword.line);
    }

    if (returnStmt->expr != nullptr){
        resolve(returnStmt->expr.get());
    }
}


LoxObject Resolver::visit(const BinaryExpr *binaryExpr) {
    resolve(binaryExpr->left.get());
    resolve(binaryExpr->right.get());
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const GroupingExpr *groupingExpr) {
    resolve(groupingExpr->expr.get());
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const UnaryExpr *unaryExpr) {
    resolve(unaryExpr->expr.get());
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const LiteralExpr *literalExpr) {
    //nothing to resolve, no variables
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const VariableExpr *variableExpr) {
    std::string name = variableExpr->identifier.lexeme;
    if (!scopes.empty()){
        Scope scope = scopes.back();
        if (scope.find(name) != scope.end() && scope.find(name)->second == false){
            throw LoxParsingError("Cannot read local variable in its own initializer", variableExpr->identifier.line);
        }
    }

    resolveLocal(variableExpr, variableExpr->identifier);
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const AssignmentExpr *assignmentExpr) {
    resolve(assignmentExpr->value.get());
    resolveLocal(assignmentExpr, assignmentExpr->identifier);
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const OrExpr *orExpr) {
    resolve(orExpr->left.get());
    resolve(orExpr->right.get());
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const AndExpr *andExpr) {
    resolve(andExpr->left.get());
    resolve(andExpr->right.get());
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const CallExpr *functionCallExpr) {
    resolve(functionCallExpr->callee.get());
    for (const auto &arg : functionCallExpr->arguments){
        resolve(arg.get());
    }
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const IncrementExpr *incrementExpr) {
    resolveLocal(incrementExpr->variable.get(), incrementExpr->variable->identifier);
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const DecrementExpr *decrementExpr) {
    resolveLocal(decrementExpr->variable.get(), decrementExpr->variable->identifier);
    return LoxObject::Nil();
}

LoxObject Resolver::visit(const LambdaExpr *lambdaExpr) {
    beginScope();
    for (const Token &param : lambdaExpr->params){
        declare(param);
        define(param);
    }
    resolve(lambdaExpr->body.get());
    endScope();
    return LoxObject::Nil();
}