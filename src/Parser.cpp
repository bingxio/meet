/**
 * Meet Programming Language Parser.
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
#include "Parser.hpp"

Parser::Parser(std::vector<Token> tokens) {
    this->tokens = std::move(tokens);
    this->statements = std::vector<Statement *>();
    this->position = 0;
}

std::vector<Statement *> Parser::parseProgram() {
    while (this->tokens.size() - 1 >= this->position && !isAtEnd())
        insertStatement(statement());
    return this->statements;
}

void Parser::insertStatement(Statement* stmt) {
    this->statements.push_back(stmt);
}

Token Parser::previous() {
    return this->tokens.at(this->position - 1);
}

Token Parser::look() {
    return this->tokens.at(this->position);
}

Token Parser::look(int pos) {
    if (this->position + pos > this->tokens.size() - 1)
        return Token(TOKEN_EOF, "EOF", 0);
    else
        return this->tokens.at(this->position + pos);
}

bool Parser::look(TokenType tokenType) {
    bool equal = look().getTokenType() == tokenType;

    if (equal)
        this->position ++;

    return equal;
}

bool Parser::isAtEnd() {
    return look(0).getTokenType() == TOKEN_EOF;
}

void Parser::error(std::string message) {
    throw std::runtime_error("[ line " + std::to_string(look().getTokenLine()) + " ] " + message);
}

Statement* Parser::statement() {
    if (look(TOKEN_VAR))
        return varStatement();
    return expressionStatement();
}

Expression* Parser::expression() {
    return assignment();
}

Expression* Parser::assignment() {
    Expression* expr = addition();

    if (look(TOKEN_EQUAL)) {
        Expression* initializer = assignment();

        if (expr->classType() == VARIABLE_EXPRESSION) {
            
        }
    }

    return expr;
}

Expression* Parser::addition() {
    Expression* expr = multiplication();

    while (look(TOKEN_PLUS) || look(TOKEN_MINUS)) {
        Token op = previous();
        Expression* right = multiplication();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::multiplication() {
    Expression* expr = unary();

    while (look(TOKEN_STAR) || look(TOKEN_SLASH)) {
        Token op = previous();
        Expression* right = unary();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::unary() {
    if (look(TOKEN_BANG) || look(TOKEN_MINUS)) {
        Token op = previous();
        Expression* expression = unary();

        return new UnaryExpression(op, expression);
    }

    return primary();
}

Expression* Parser::primary() {
    if (look(TOKEN_VALUE_INT) || look(TOKEN_VALUE_STRING) || look(TOKEN_VALUE_FLOAT))
        return new LiteralExpression(previous());

    if (look(TOKEN_VALUE_IDENTIFIER))
        return new VariableExpression(previous());
    
    if (look(TOKEN_LPAREN)) {
        Expression* expr = expression();

        if (look(TOKEN_RPAREN) == false)
            error("parsing error: expect ')' after expression.");
        
        return new GroupExpression(expr);
    }

    if (look(TOKEN_NULL) || look(TOKEN_TRUE) || look(TOKEN_FALSE))
        return new LiteralExpression(previous());

    error("parsing error: illegal expression.");

    return NULL;
}

Statement* Parser::expressionStatement() {
    return new ExpressionStatement(expression());
}

Statement* Parser::varStatement() {
    std::string name = look().getTokenLiteral();

    if (look(TOKEN_VALUE_IDENTIFIER) == false)
        error("parsing error: variable name can only be english character sequences.");

    if (look(TOKEN_EQUAL) == false)
        error("parsing error: expect '=' after var keyword.");

    Expression* initializer = expression();

    if (look(TOKEN_COMMA)) {
        std::map<std::string, Expression *> list = std::map<std::string, Expression *>();
    }
}