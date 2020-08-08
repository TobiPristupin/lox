#include "Resolver.h"
#include "LoxError.h"


std::unordered_map<const Expr*, int> Resolver::resolve(const std::vector<UniqueStmtPtr> &stmts) {
    for (auto const &stmt : stmts){
        resolve(stmt.get());
    }

    return distances;
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
    resolve(whileStmt->condition.get());
    resolve(whileStmt->body.get());
}

void Resolver::visit(const BreakStmt *breakStmt) {}

void Resolver::visit(const ContinueStmt *continueStmt) {}

void Resolver::visit(const ForStmt *forStmt) {
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
    resolveFunction(functionStmt);
}

void Resolver::resolveFunction(const FunctionDeclStmt *functionStmt) {
    beginScope();
    for (const Token &param : functionStmt->params){
        declare(param);
        define(param);
    }

    resolve(functionStmt->body);
    endScope();
}

void Resolver::visit(const ReturnStmt *returnStmt) {
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

LoxObject Resolver::visit(const FunctionCallExpr *functionCallExpr) {
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