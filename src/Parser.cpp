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

Statement* Parser::statement() {
    if (look(TOKEN_VAR)) 
        std::cout << "Parse var statement." << std::endl;
    return expressionStatement();
}

Expression* Parser::expression() {
    return addition();
}

Expression* Parser::addition() {
    Expression* expr = multiplication();

    if (look(TOKEN_PLUS) || look(TOKEN_MINUS)) {
        Token op = previous();
        Expression* right = multiplication();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::multiplication() {
    Expression* expr = primary();

    if (look(TOKEN_STAR) || look(TOKEN_SLASH)) {
        Token op = previous();
        Expression* right = primary();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::primary() {
    if (look(TOKEN_VALUE_INT))
        return new LiteralExpression(previous());
    throw std::runtime_error("parsing error: unknown token -> " + look().getTokenLiteral());
}

ExpressionStatement* Parser::expressionStatement() {
    return new ExpressionStatement(expression());
}