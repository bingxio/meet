/**
 * Meet Programming Language Statement.
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
#ifndef MEET_FOR_STATEMENT_H
#define MEET_FOR_STATEMENT_H

#include <sstream>

#include "../Statement.hpp"

#include "BlockStatement.hpp"

class ForStatement: public Statement {
    public:
        Statement* initializer;
        Statement* condition;
        Statement* renovate;

        BlockStatement* block;

        ForStatement(Statement* a, Statement* b, Statement* c, BlockStatement* d):
            initializer(a), condition(b), renovate(c), block(d) {}

        ~ForStatement() {
            delete initializer;
            delete condition;
            delete renovate;
        }

        std::string defintion() {
            return STATEMENT_FOR;
        }

        std::string toString() {
            std::stringstream data;

            data << "[ ForStatement: initializer = " << initializer->toString() << ", condition = ";
            data << condition->toString() << ", renovate = " << renovate->toString() << ", block = ";

            data << block->toString() << " ]";

            return data.str();
        }
};

#endif