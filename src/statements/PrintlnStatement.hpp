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
#ifndef MEET_PRINTLN_STATEMENT_H
#define MEET_PRINTLN_STATEMENT_H

#include "../interpreter/Statement.hpp"
#include "../interpreter/Expression.hpp"

class PrintlnStatement: public Statement {
    public:
        Expression* expression;

        bool cls;

        PrintlnStatement(Expression* expression, bool cls): expression(std::move(expression)), cls(cls) {}

        ~PrintlnStatement() {
            delete expression;
            delete &cls;
        }

        std::string defintion() {
            return STATEMENT_PRINTLN;
        }

        std::string toString() {
            return "[ PrintlnStatement: expr = " + expression->toString() + 
                ", cls = " + (cls ? "true" : "false") + " ]";
        }
};

#endif