/**
 * Meet Programming Language Expression.
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
#ifndef MEET_ASSIGN_EXPRESSION_H
#define MEET_ASSIGN_EXPRESSION_H

#include "../Expression.hpp"
#include "../Token.hpp"

class AssignExpression: public Expression {
    public:
        Token name;

        Expression* initializer;

        Token typed;

        bool isVar = false;

        AssignExpression(Token name, Expression* initializer, Token typed): name(std::move(name)),
            initializer(std::move(initializer)), typed(std::move(typed)) {}

        ~AssignExpression() {
            delete &name;
            delete initializer;
            delete &typed;
            delete &isVar;
        }

        std::string classType() {
            return EXPRESSION_ASSIGN;
        }

        std::string toString() {
            return "[ AssignExpression: name = " + name.literal + ", initializer = " +
                initializer->toString() + ", isVar = " + (isVar ? "true" : "false") + " ]";
        }
};

#endif