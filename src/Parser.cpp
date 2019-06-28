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

    if (look(TOKEN_FOR))
        return forStatement();

    if (look(TOKEN_BREAK))
        return breakStatement();

    if (look(TOKEN_CONTINUE))
        return continueStatement();

    if (look(TOKEN_IF))
        return ifStatement();

    if (look(TOKEN_WHILE))
        return whileStatement();

    if (look(TOKEN_FUN))
        return funStatement();

    return expressionStatement();
}

Expression* Parser::expression() {
    return assignment();
}

Expression* Parser::assignment() {
    Expression* expr = logicalOr();

    /**
     * var a = 12   : AssignExpression
     */
    if (look(TOKEN_EQUAL)) {
        Expression* initializer = assignment();

        if (expr->defintion() == EXPRESSION_VARIABLE) {
            Token name = ((VariableExpression *) expr)->name;

            return new AssignExpression(name, initializer, Token(TOKEN_ANY, "any", name.line));
        }

        error("syntax error: invalid assignment target.");
    }

    /**
     * var a: int = 12  : AssignExpression
     */
    if (look(TOKEN_COLON)) {
        Token name = look(-2);
        Token type = look();

        if (isTyped(type)) {
            this->position ++;
        
            if (look(TOKEN_EQUAL) == false)
                return new AssignExpression(name, nullptr, type);

            Expression* initializer = expression();

            return new AssignExpression(name, initializer, type);

            error("syntax error: unknown variable type " + look().literal + ".");
        }
    }

    return expr;
}

/**
 * LogicalExpression:
 * 
 * 1 or 2
 * 2 | 2
 */
Expression* Parser::logicalOr() {
    Expression* expr = logicalAnd();

    while (look(TOKEN_OR)) {
        Token op = previous();
        Expression* right = logicalAnd();

        expr = new LogicalExpression(expr, op, right);
    }

    return expr;
}

/**
 * LogicalExpression:
 * 
 * 1 and 2
 * 1 & 2
 */
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

    while (look(TOKEN_STAR) || look(TOKEN_SLASH) || look(TOKEN_STAR_EQUAL) || look(TOKEN_SLASH_EQUAL) || 
            look(TOKEN_MODULAR)) {
        Token op = previous();
        Expression* right = unary();

        expr = new BinaryExpression(expr, op, right);
    }

    return expr;
}

/**
 * UnaryExpression:
 * 
 * !a
 * -123
 */
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

    if (look(TOKEN_NULL) || look(TOKEN_TRUE) || look(TOKEN_FALSE))
        return new LiteralExpression(previous());

    if (look(TOKEN_VALUE_IDENTIFIER)) {
        Token name = previous();

        /**
         * a [0]        : GetExpression
         * a [0] = 123  : SetExpression
         */
        if (look(TOKEN_LBRACKET)) {
            Expression* initializer = expression();

            if (look(TOKEN_RBRACKET) == false)
                error("syntax error: expect ']' after expression.");

            if (look(TOKEN_EQUAL)) {
                Expression* value = expression();

                if (look(TOKEN_MINUS_GREATER))
                    return new SetExpression(name, initializer, value, statement(), EXPRESSION_LIST);

                return new SetExpression(name, initializer, value, NULL, EXPRESSION_LIST);
            }

            return new GetExpression(name, initializer, EXPRESSION_LIST);
        }

        /**
         * CallExpression: 
         * 
         * hello ()
         * hello (a, 123, 'world')
         */
        if (look(TOKEN_LPAREN)) {
            std::vector<Value> parameters = std::vector<Value>();

            while (look(TOKEN_RPAREN) == false) {
                if (look(TOKEN_COMMA))
                    continue;
                else {
                    parameters.push_back(backValueWithToken(look()));

                    this->position ++;
                }
            }

            return new CallExpression(name, parameters);
        }

        return new VariableExpression(name);
    }

    /**
     * (1 + 4 * 3)  : GroupExpression
     */
    if (look(TOKEN_LPAREN)) {
        Expression* expr = expression();

        if (look(TOKEN_RPAREN) == false)
            error("syntax error: expect ')' after expression.");
        
        return new GroupExpression(expr);
    }

    if (look(TOKEN_LBRACKET)) {
        std::vector<Value> values = std::vector<Value>();

        while (look(TOKEN_RBRACKET) == false) {
            if (look(TOKEN_COMMA))
                continue;
                
            values.push_back(backValueWithToken(look()));

            this->position ++;
        }

        return new ListExpression(values);
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
        look(TOKEN_COMMA);

        Expression* expr = expression();

        if (expr->defintion() == EXPRESSION_VARIABLE && look().type == TOKEN_COLON) {
            expr = expression();

            if (expr->defintion() != EXPRESSION_ASSIGN)
                error("syntax error: variable initializer must be assignment.");

            list.push_back((AssignExpression *) expr);

            continue;
        }

        if (expr->defintion() != EXPRESSION_ASSIGN)
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

Statement* Parser::minusGreaterBlockStatement() {
    std::vector<Statement *> block = std::vector<Statement *>();

    block.push_back(statement());

    return new BlockStatement(block);
}

Statement* Parser::blockStatement() {
    std::vector<Statement *> block = std::vector<Statement *>();

    while (look(TOKEN_RBRACE) == false) {
        block.push_back(statement());

        if (isAtEnd())
            error("syntax error: lost right '}' after block statement.");
    }

    return new BlockStatement(block);
}

Statement* Parser::breakStatement() {
    return new BreakStatement();
}

Statement* Parser::continueStatement() {
    return new ContinueStatement();
}

Statement* Parser::forStatement() {
    Statement* initializer = statement();

    if (look(TOKEN_SEMICOLON) == false)
        error("syntax error: expect ';' after initializer.");

    Statement* condition = statement();

    if (look(TOKEN_SEMICOLON) == false)
        error("syntax error: expect ';' after condition.");

    Statement* renovate = statement();

    std::vector<Statement *> block = std::vector<Statement *>();

    if (look(TOKEN_MINUS_GREATER))
        block.push_back(statement());
    else if (look(TOKEN_LBRACE))
        return new ForStatement(initializer, condition, renovate, (BlockStatement *) blockStatement());
    else
        error("syntax error: exepct '{' or '->' after for statement.");

    return new ForStatement(initializer, condition, renovate, new BlockStatement(block));
}

Statement* Parser::ifStatement() {
    IfStatement* ifStatement = new IfStatement;

    ifStatement->establish = nullptr;
    ifStatement->elifCondition = nullptr;
    ifStatement->elifEstablish = nullptr;
    ifStatement->elseEstablish = nullptr;

    ifStatement->condition = statement();

    if (look(TOKEN_MINUS_GREATER))
        ifStatement->establish = (BlockStatement *) minusGreaterBlockStatement();
    else if (look(TOKEN_LBRACE))
        ifStatement->establish = (BlockStatement *) blockStatement();
    else
        error("syntax error: exepct '{' or '->' after if statement condition.");

    if (look(TOKEN_ELIF)) {
        ifStatement->elifCondition = statement();

        if (look(TOKEN_MINUS_GREATER))
            ifStatement->elifEstablish = (BlockStatement *) minusGreaterBlockStatement();
        else if (look(TOKEN_LBRACE))
            ifStatement->elifEstablish = (BlockStatement *) blockStatement();
        else
            error("syntax error: exepct '{' or '->' after if statement condition.");
    }
    
    if (look(TOKEN_ELSE))
        if (look(TOKEN_MINUS_GREATER))
            ifStatement->elseEstablish = (BlockStatement *) minusGreaterBlockStatement();
        else if (look(TOKEN_LBRACE))
            ifStatement->elseEstablish = (BlockStatement *) blockStatement();
        else
            error("syntax error: exepct '{' or '->' after if statement condition.");

    return ifStatement;
}

Statement* Parser::whileStatement() {
    WhileStatement* whileStatement = new WhileStatement;

    whileStatement->condition = statement();

    if (look(TOKEN_MINUS_GREATER))
        whileStatement->block = (BlockStatement *) minusGreaterBlockStatement();
    else if (look(TOKEN_LBRACE))
        whileStatement->block = (BlockStatement *) blockStatement();
    else
        error("syntax error: exepct '{' or '->' after while statement condition.");

    return whileStatement;
}

Statement* Parser::funStatement() {
    FunctionStatement* funStatement = new FunctionStatement;

    if (look(TOKEN_VALUE_IDENTIFIER) == false)
        error("syntax error: cannot use function name without identifier.");

    Token name = previous();

    if (look(TOKEN_LPAREN) == false)
        error("syntax error: expect '(' after function name.");

    std::map<std::string, std::string> parameters = std::map<std::string, std::string>();

    while (look(TOKEN_RPAREN) == false) {
        if (look(TOKEN_COLON))
            parameters.insert(std::pair<std::string, std::string>(look(-2).literal, look().literal));
        this->position ++;
    }

    funStatement->name = name;
    funStatement->parameters = parameters;

    if (look(TOKEN_COLON)) {
        funStatement->returnType = look();

        this->position ++;
    }

    if (look(TOKEN_MINUS_GREATER))
        funStatement->block = (BlockStatement *) minusGreaterBlockStatement();
    else if (look(TOKEN_LBRACE))
        funStatement->block = (BlockStatement *) blockStatement();
    else
        error("syntax error: exepct '{' or '->' after function statement.");

    return funStatement;
}