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
#ifndef MEET_IF_STATEMENT_H
#define MEET_IF_STATEMENT_H

#include <sstream>

#include "../Statement.hpp"
#include "BlockStatement.hpp"

class IfStatement: public Statement {
    public:
        Statement* condition;
        BlockStatement* establish;

        Statement* elifCondition;
        BlockStatement* elifEstablish;

        BlockStatement* elseEstablish;

        ~IfStatement() {
            delete condition;
            delete establish;
            delete elifCondition;
            delete elifEstablish;
            delete elseEstablish;
        }

        std::string defintion() {
            return STATEMENT_IF;
        }

        std::string toString() {
            std::stringstream data;

            data << "[ IfStatement: ";
            data << "condition = " << condition->toString();

            if (establish != nullptr)
                data << ", establish = " << establish->toString();

            if (elifCondition != nullptr)
                data << ", elifCondition = " << elifCondition->toString();

            if (elifEstablish != nullptr)
                data << ", elifEstablish = " << elifEstablish->toString();

            if (elseEstablish != nullptr)
                data << ", elseEstablish = " << elseEstablish->toString();

            data << " ]";
            

            return data.str();
        }
};

#endif