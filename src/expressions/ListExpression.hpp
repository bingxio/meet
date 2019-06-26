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
#ifndef MEET_LIST_EXPRESSION_H
#define MEET_LIST_EXPRESSION_H

#include "../Expression.hpp"

class ListExpression: public Expression {
    public:
        std::vector<Value> values;

        ListExpression(std::vector<Value> values): values(std::move(values)) {}

        ~ListExpression() {
            values.clear();

            std::vector<Value>().swap(values);
        }

        std::string defintion() {
            return EXPRESSION_LIST;
        }

        std::string toString() {
            return "[ ListExpression: size = " + std::to_string(values.size()) + " ]";
        }
};

#endif