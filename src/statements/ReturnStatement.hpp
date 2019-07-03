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
#ifndef MEET_RETURN_STATEMENT_H
#define MEET_RETURN_STATEMENT_H

#include <exception>

#include "../interpreter/Statement.hpp"
#include "../interpreter/Expression.hpp"

class ReturnStatement: public Statement, std::exception {
    public:
        Expression* expression;

        ReturnStatement(Expression* expression): expression(std::move(expression)) {}

        ~ReturnStatement() {
            delete expression;
        }

        std::string defintion() {
            return STATEMENT_RETURN;
        }

        std::string toString() {
            return "[ ReturnStatement: expr = " + expression->toString() + " ]";
        }
};

#endif