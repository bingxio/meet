/**
 * Meet Programming Language Interpreter.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Copyright (c) 2019 Turaiiao
 * Email: 1171840237@qq.com
 * Github: https://github.com/turaiiao
 */
#include "Interpreter.hpp"

Interpreter::Interpreter(std::vector<Statement *> statements, bool replMode) {
    this->statements = std::move(statements);
    this->environment = std::map<Token, Value>();
    this->size = this->statements.size();
    this->position = 0;
    this->replMode = replMode;
}

void Interpreter::assign(Token token, Value value) {
    this->environment.insert(std::pair<Token, Value>(token, value));

    this->get(token).printValue(); // NULL
}

Value Interpreter::get(Token token) {
    std::map<Token, Value>::iterator a = this->environment.find(token);

    if (a == this->environment.end())
        throw std::runtime_error("undefined variable: '" + token.literal + "'.");

    return a->second;
}

Statement* Interpreter::look() {
    return this->statements.at(this->position);
}

int Interpreter::removeStatement(int pos) {
    std::vector<Statement *>::iterator a = this->statements.begin() + pos;

    if (*a == NULL)
        return 0;
    else {
        this->statements.erase(a);
        this->position --;

        return this->statements.size();
    }
}

void Interpreter::execute() {
    while (this->size) {
        if (look()->classType() == STATEMENT_EXPRESSION)
            executeExpressionStatement();
        
        if (look()->classType() == STATEMENT_VAR)
            executeVarStatement();

        this->size = removeStatement(this->position ++);
    }
}

Value Interpreter::executeExpression(Expression* expr) {
    if (expr->classType() == EXPRESSION_LITERAL)
        return executeLiteralExpression(expr);

    if (expr->classType() == EXPRESSION_BINARY)
        return executeBinaryExpression(expr);

    if (expr->classType() == EXPRESSION_GROUP)
        return executeGroupExpression(expr);

    if (expr->classType() == EXPRESSION_UNARY)
        return executeUnaryExpression(expr);

    if (expr->classType() == EXPRESSION_ASSIGN)
        return executeAssignExpression(expr);

    throw std::runtime_error("type error: unknow expression.");
}

Value Interpreter::executeLiteralExpression(Expression* expr) {
    return backValueWithToken(((LiteralExpression *) expr)->token);
}

Value Interpreter::executeBinaryExpression(Expression* expr) {
    BinaryExpression* a = (BinaryExpression *) expr;

    Value l = executeExpression(a->left);
    Value r = executeExpression(a->right);

    if (a->token.type == TOKEN_PLUS)          return l + r;
    if (a->token.type == TOKEN_MINUS)         return l - r;
    if (a->token.type == TOKEN_STAR)          return l * r;
    if (a->token.type == TOKEN_SLASH)         return l / r;
    if (a->token.type == TOKEN_MODULAR)       return l % r;
    if (a->token.type == TOKEN_GREATER)       return l > r;
    if (a->token.type == TOKEN_GREATER_EQUAL) return l >= r;
    if (a->token.type == TOKEN_LESS)          return l < r;
    if (a->token.type == TOKEN_LESS_EQUAL)    return l <= r;
    if (a->token.type == TOKEN_BANG_EQUAL)    return l != r;
    if (a->token.type == TOKEN_EQUAL_EQUAL)   return l == r;

    throw std::runtime_error("type error: unknow operator for binary expression.");
}

Value Interpreter::executeGroupExpression(Expression* expr) {
    return executeExpression(((GroupExpression *) expr)->expression);
}

Value Interpreter::executeUnaryExpression(Expression* expr) {
    UnaryExpression* unaryExpr = (UnaryExpression *) expr;

    Value a = executeExpression(unaryExpr->expression);

    if (unaryExpr->token.type == TOKEN_BANG) {

        if (a.valueBool)
            return Value(!a.boolValue);

        if (a.valueNumber)
            return Value(!a.numberValue);

        throw std::runtime_error("type error: unknow operator for unary expression.");
    }

    if (unaryExpr->token.type == TOKEN_MINUS) {

        if (a.valueNumber)
            return Value(-a.numberValue);

        throw std::runtime_error("type error: unknow operator for unary expression.");
    }

    throw std::runtime_error("type error: unknow operator for unary expression.");
}

Value Interpreter::executeAssignExpression(Expression* expr) {
    AssignExpression* assignExpr = (AssignExpression *) expr;

    Value value = executeExpression(assignExpr->initializer);

    this->assign(assignExpr->name, value);

    return value;
}

Value Interpreter::executeExpressionStatement() {
    Value a = executeExpression(((ExpressionStatement *) look())->expression);

    if (this->replMode)
        a.printValue();

    return a;
}

void Interpreter::executeVarStatement() {
    VarStatement* stmt = (VarStatement *) look();

    for (auto i : stmt->list)
        executeExpression(i);
}