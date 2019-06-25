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
#ifndef MEET_WHILE_STATEMENT_H
#define MEET_WHILE_STATEMENT_H

#include "../Statement.hpp"
#include "BlockStatement.hpp"

class WhileStatement: public Statement {
    public:
        Statement* condition;

        BlockStatement* block;

        ~WhileStatement() {
            delete condition;
            delete block;
        }

        std::string defintion() {
            return STATEMENT_WHILE;
        }

        std::string toString() {
            return "[ WhileStatement: condition = " + condition->toString() + 
                ", block = " + block->toString() + " ]";
        }
};

#endif