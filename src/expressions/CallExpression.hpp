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
#ifndef MEET_CALL_EXPRESSION_H
#define MEET_CALL_EXPRESSION_H

#include "../Expression.hpp"
#include "../Token.hpp"
#include "../Value.hpp"

class CallExpression: public Expression {
    public:
        Token name;

        std::vector<Value> parameters;

        CallExpression(Token name, std::vector<Value> parameters) {
            this->name = std::move(name);
            this->parameters = std::move(parameters);
        }

        std::string defintion() {
            return EXPRESSION_CALL;
        }

        std::string toString() {
            return "[ CallExpression: name = " + name.literal + ", parameters = ";
        }
};

#endif