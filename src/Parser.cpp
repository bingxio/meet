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
    bool equal = look().type == tokenType;

    if (equal)
        this->position ++;

    return equal;
}

bool Parser::isAtEnd() {
    return look(0).type == TOKEN_EOF;
}

void Parser::error(std::string message) {
    throw std::runtime_error("[ line " + std::to_string(look().line) + " ] " + message);
}

Statement* Parser::statement() {
    if (look(TOKEN_VAR))
        return varStatement();
    
    if (look(TOKEN_PRINTLN) || look(TOKEN_PRINT))
        return printlnStatement();

    if (look(TOKEN_LBRACE))
        return blockStatement();

    return expressionStatement();
}

Expression* Parser::expression() {
    return assignment();
}

Expression* Parser::assignment() {
    Expression* expr = logicalOr();

    if (look(TOKEN_EQUAL)) {
        Expression* initializer = assignment();

        if (expr->classType() == EXPRESSION_VARIABLE) {
            Token name = ((VariableExpression *) expr)->name;

            return new AssignExpression(name, initializer, Token(TOKEN_ANY, "", 0));
        }

        error("syntax error: invalid assignment target.");
    }

    if (look(TOKEN_COLON)) {
        Token name = look(-2);
        Token type = look();

        if (isTyped(type)) {
            this->position ++;
        
            if (look(TOKEN_EQUAL) == false)
                error("syntax error: missing equal for assign expression.");

            Expression* initializer = expression();

            return new AssignExpression(name, initializer, type);

            error("syntax error: unknown variable type " + look().literal + ".");
        }
    }

    return expr;
}

Expression* Parser::logicalOr() {
    Expression* expr = logicalAnd();

    while (look(TOKEN_OR)) {
        Token op = previous();
        Expression* right = logicalAnd();

        expr = new LogicalExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::logicalAnd() {
    Expression* expr = equality();

    while (look(TOKEN_AND)) {
        Token op = previous();
        Expression* right = equality();

        expr = new LogicalExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::equality() {
    Expression* expr = comparison();

    while (look(TOKEN_EQUAL_EQUAL) || look(TOKEN_BANG_EQUAL)) {
        Token op = previous();
        Expression* right = comparison();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::comparison() {
    Expression* expr = addition();

    while (look(TOKEN_GREATER) || look(TOKEN_GREATER_EQUAL) ||
            look(TOKEN_LESS) || look(TOKEN_LESS_EQUAL)) {
        Token op = previous();
        Expression* right = addition();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::addition() {
    Expression* expr = multiplication();

    while (look(TOKEN_PLUS) || look(TOKEN_MINUS) || look(TOKEN_PLUS_EQUAL) || look(TOKEN_MINUS_EQUAL)) { 
        Token op = previous();
        Expression* right = multiplication();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::multiplication() {
    Expression* expr = unary();

    while (look(TOKEN_STAR) || look(TOKEN_SLASH) || look(TOKEN_STAR_EQUAL) || look(TOKEN_SLASH_EQUAL)) {
        Token op = previous();
        Expression* right = unary();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

Expression* Parser::unary() {
    if (look(TOKEN_BANG) || look(TOKEN_MINUS)) {
        Token op = previous();
        Expression* expression =    unary();

        return new UnaryExpression(op, expression);
    }

    return primary();
}

Expression* Parser::primary() {
    if (look(TOKEN_VALUE_INT) || look(TOKEN_VALUE_STRING) || look(TOKEN_VALUE_FLOAT))
        return new LiteralExpression(previous());

    if (look(TOKEN_VALUE_IDENTIFIER))
        return new VariableExpression(previous());
    
    if (look(TOKEN_NULL) || look(TOKEN_TRUE) || look(TOKEN_FALSE))
        return new LiteralExpression(previous());

    if (look(TOKEN_LPAREN)) {
        Expression* expr = expression();

        if (look(TOKEN_RPAREN) == false)
            error("syntax error: expect ')' after expression.");
        
        return new GroupExpression(expr);
    }

    error("syntax error: illegal expression, token '" + look().literal + "'.");

    return NULL;
}

Statement* Parser::expressionStatement() {
    return new ExpressionStatement(expression());
}

Statement* Parser::varStatement() {
    std::vector<AssignExpression *> list = std::vector<AssignExpression *>();

    bool firstParseStatement = true;

    while (firstParseStatement || look().type == TOKEN_COMMA) {
        if (look().type == TOKEN_COMMA)
            this->position ++;

        Expression* expr = expression();

        if (expr->classType() == EXPRESSION_VARIABLE && look().type == TOKEN_COLON) {
            expr = expression();

            if (expr->classType() != EXPRESSION_ASSIGN)
                error("syntax error: variable initializer must be assignment.");

            list.push_back((AssignExpression *) expr);

            continue;
        }

        if (expr->classType() != EXPRESSION_ASSIGN)
            error("syntax error: variable initializer must be assignment.");
        
        list.push_back((AssignExpression *) expr);

        firstParseStatement = false;
    }

    for (auto i : list) i->isVar = true;

    return new VarStatement(list);
}

Statement* Parser::printlnStatement() {
    bool cls = look(-1).literal == TOKEN_PRINTLN ? true : false;

    return new PrintlnStatement(expression(), cls);
}

Statement* Parser::blockStatement() {
    std::vector<Statement *> block = std::vector<Statement *>();

    while (look().type != TOKEN_RBRACE)
        block.push_back(this->statement());

    this->position ++;

    return new BlockStatement(block);
}