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

Interpreter::Interpreter(std::vector<Statement *> statements, std::map<std::string, Value>* environment) {
    this->statements = std::move(statements);
    this->environment = environment;
    this->size = this->statements.size();
    this->position = 0;
    this->replMode = replMode;
}

void Interpreter::assign(std::string name, Value value) {
    this->environment->insert(std::pair<std::string, Value>(name, value));
}

void Interpreter::reAssign(std::string name, Value value) {
    std::map<std::string, Value>::iterator a = this->environment->find(name);

    this->environment->erase(a);
    this->assign(name, value);
}

Value Interpreter::get(std::string name) {
    std::map<std::string, Value>::iterator a = this->environment->find(name);

    if (a == this->environment->end())
        throw std::runtime_error("undefined variable: '" + name + "'.");

    return a->second;
}

bool Interpreter::haveObject(std::string name) {
    return this->environment->find(name) != this->environment->end();
}

Statement* Interpreter::look() {
    return this->statements.at(this->position);
}

int Interpreter::removeStatement(int pos) {
    std::vector<Statement *>::iterator a = this->statements.begin() + pos;

    if (a == this->statements.end())
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

        if (look()->classType() == STATEMENT_PRINTLN)
            executePrintlnStatement();

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

    if (expr->classType() == EXPRESSION_LOGICAL)
        return executeLogicalExpression(expr);

    if (expr->classType() == EXPRESSION_VARIABLE)
        return executeVariableExpression(expr);

    throw std::runtime_error("interpret error: unknow expression.");
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

    throw std::runtime_error("interpret error: unknow operator for binary expression.");
}

Value Interpreter::executeGroupExpression(Expression* expr) {
    return executeExpression(((GroupExpression *) expr)->expression);
}

Value Interpreter::executeUnaryExpression(Expression* expr) {
    UnaryExpression* unaryExpr = (UnaryExpression *) expr;

    Value a = executeExpression(unaryExpr->expression);

    if (unaryExpr->token.type == TOKEN_BANG) {
        if (a.valueNumber)
            return Value(!a.numberValue);

        if (a.valueBool)
            return Value(!a.boolValue);

        throw std::runtime_error("interpret error: unknow operator for unary expression.");
    }

    if (unaryExpr->token.type == TOKEN_MINUS) {
        if (a.valueNumber)
            return Value(-a.numberValue);

        throw std::runtime_error("interpret error: unknow operator for unary expression.");
    }

    throw std::runtime_error("interpret error: unknow operator for unary expression.");
}

Value Interpreter::executeAssignExpression(Expression* expr) {
    AssignExpression* assignExpr = (AssignExpression *) expr;

    Value value = executeExpression(assignExpr->initializer);

    value.varAny = true;

    if (assignExpr->isVar) {
        if (this->haveObject(assignExpr->name.literal))
            throw std::runtime_error("interpret error: repeatedly defining variavle '" + assignExpr->name.literal + "'");

        if (assignExpr->typed.literal != "") {
            if (assignExpr->typed.literal == TOKEN_ANY)
                value.varAny = true;
            else if (assignExpr->typed.literal == TOKEN_INT && value.valueNumber)
                value.varNumber = true;
            else if (assignExpr->typed.literal == TOKEN_STRING && value.valueString)
                value.varString = true;
            else if (assignExpr->typed.literal == TOKEN_BOOLEAN && value.valueBool)
                value.varBoolean = true;

            if (!value.varNumber && !value.varString && !value.varBoolean)
                throw std::runtime_error("interpret error: the initialization value type is defferent from the specified type.");
        }

        this->assign(assignExpr->name.literal, value);
    } else {
        Value a = this->get(assignExpr->name.literal);

        if ((a.varNumber && value.valueNumber == false) || (a.varString && value.valueString == false) ||
            (a.varBoolean && value.valueBool == false)) {
            throw std::runtime_error("interpret error: cannot defined as other type.");
        }

        this->reAssign(assignExpr->name.literal, value);
    }

    return value;
}

Value Interpreter::executeLogicalExpression(Expression* expr) {
    LogicalExpression* logicalExpr = (LogicalExpression *) expr;

    Value a = executeExpression(logicalExpr->left);
    Value b = executeExpression(logicalExpr->right);

    if (logicalExpr->token.type == TOKEN_OR)
        return a || b;

    return a && b;
}

Value Interpreter::executeVariableExpression(Expression* expr) {
    VariableExpression* varExpr = (VariableExpression *) expr;

    return this->get(varExpr->name.literal);
}

Value Interpreter::executeExpressionStatement() {
    Value a = executeExpression(((ExpressionStatement *) look())->expression);

    return a;
}

void Interpreter::executeVarStatement() {
    VarStatement* stmt = (VarStatement *) look();

    for (auto i : stmt->list)
        executeExpression(i);
}

void Interpreter::executePrintlnStatement() {
    PrintlnStatement* stmt = (PrintlnStatement *) look();

    Value a = executeExpression(stmt->expression);

    if (stmt->cls)
        a.printLineValue();
    else
        a.printValue();
}