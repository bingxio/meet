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
#ifndef MEET_LOGICAL_EXPRESSION_H
#define MEET_LOGICAL_EXPRESSION_H

#include "../Token.hpp"
#include "../interpreter/Expression.hpp"

class LogicalExpression: public Expression {
    public:
        Expression* left;

        Token token;

        Expression* right;

        LogicalExpression(Expression* left, Token token, Expression* right): left(std::move(left)),
            token(std::move(token)), right(std::move(right)) {}

        ~LogicalExpression() {
            delete left;
            delete &token;
            delete right;
        }

        std::string defintion() {
            return EXPRESSION_LOGICAL;
        }

        std::string toString() {
            return "[ LogicalExpr: left = " + left->toString() + ", operator = " + token.literal + ", right = "
                + right->toString() + " ]";
        }
};

#endif