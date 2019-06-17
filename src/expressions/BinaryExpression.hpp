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
#ifndef MEET_BINARY_EXPRESSION_HPP
#define MEET_BINARY_EXPRESSION_HPP

#include "../Expression.hpp"
#include "../Token.hpp"

class BinaryExpression: public Expression {
    private:
        Expression* left;
        Expression* right;

        Token op;
    public:
        explicit BinaryExpression(Expression* left, Token op, Expression* right):
            left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

        ~BinaryExpression() {
            delete left;
            delete right;
            delete &op;
        }

        std::string toString() {
            return "BinaryExpression";
        }
};

#endif