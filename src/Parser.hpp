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
#ifndef MEET_PARSER_H
#define MEET_PARSER_H

#include <vector>

#include "Statement.hpp"
#include "Expression.hpp"
#include "Token.hpp"
#include "Value.hpp"

#include "expressions/LiteralExpression.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/GroupExpression.hpp"
#include "expressions/VariableExpression.hpp"
#include "expressions/UnaryExpression.hpp"
#include "expressions/AssignExpression.hpp"
#include "expressions/LogicalExpression.hpp"
#include "expressions/ListExpression.hpp"

#include "statements/ExpressionStatement.hpp"
#include "statements/VarStatement.hpp"
#include "statements/PrintlnStatement.hpp"
#include "statements/BlockStatement.hpp"
#include "statements/ForStatement.hpp"
#include "statements/BreakStatement.hpp"
#include "statements/ContinueStatement.hpp"
#include "statements/IfStatement.hpp"
#include "statements/WhileStatement.hpp"

class Parser {
    private:
        std::vector<Token> tokens;
        std::vector<Statement *> statements;

        int position;

        Token look();
        Token look(int pos);
        Token previous();

        bool isAtEnd();
        bool look(TokenType tokenType);

        void error(std::string message);
        void insertStatement(Statement* stmt);
        
        Expression* expression();
        Expression* assignment();
        Expression* logicalOr();
        Expression* logicalAnd();
        Expression* equality();
        Expression* comparison();
        Expression* addition();
        Expression* multiplication();
        Expression* unary();
        Expression* call();
        Expression* finishCall();
        Expression* primary();

        Statement* minusGreaterBlockStatement();

        Statement* statement();
        Statement* expressionStatement();
        Statement* varStatement();
        Statement* printlnStatement();
        Statement* blockStatement();
        Statement* forStatement();
        Statement* breakStatement();
        Statement* continueStatement();
        Statement* ifStatement();
        Statement* whileStatement();
    public:
        explicit Parser(std::vector<Token> tokens);

        std::vector<Statement *> parseProgram();
};

#endif