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
#ifndef MEET_INTERPRETER_H
#define MEET_INTERPRETER_H

#include <vector>

#include "Value.hpp"
#include "Statement.hpp"
#include "Expression.hpp"

#include "expressions/LiteralExpression.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/GroupExpression.hpp"
#include "expressions/UnaryExpression.hpp"

#include "statements/ExpressionStatement.hpp"

class Interpreter {
    private:
        std::vector<Statement *> statements;

        int size;
        int position;

        int removeStatement(int pos);

        bool replMode = false;

        Statement* look();

        void executeVarStatement();

        Value executeExpressionStatement();
        Value executeExpression(Expression* expr);
        Value executeLiteralExpression(Expression* expr);
        Value executeBinaryExpression(Expression* expr);
        Value executeGroupExpression(Expression* expr);
        Value executeUnaryExpression(Expression* expr);
    public:
        explicit Interpreter(std::vector<Statement *> statements, bool replMode);

        void execute();
};

#endif