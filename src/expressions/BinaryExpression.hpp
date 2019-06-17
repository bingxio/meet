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
    public:
        Expression* left;
        Expression* right;

        Token token;

        explicit BinaryExpression(Expression* left, Token token, Expression* right):
            left(std::move(left)), token(std::move(token)), right(std::move(right)) {}

        ~BinaryExpression() {
            delete left;
            delete right;
            delete &token;
        }

        std::string classType() {
            return EXPRESSION_BINARY;
        }

        std::string toString() {
            return "[ BinaryExpression: left = " + left->toString() + ", token = " + token.literal  + 
                ", right = " + right->toString() + " ]";
        }
};

#endif