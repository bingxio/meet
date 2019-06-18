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
    this->size = this->statements.size();
    this->position = 0;
    this->replMode = replMode;
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

    throw std::runtime_error("type error: unknow operator for binary expression.");
}

Value Interpreter::executeExpressionStatement() {
    Value a = executeExpression(((ExpressionStatement *) look())->expression);

    if (this->replMode)
        a.printValue();

    return a;
}

void Interpreter::executeVarStatement() {

}