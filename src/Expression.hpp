/**
 * Meet Programming Language Expression Statement.
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
#ifndef MEET_EXPRESSION_H
#define MEET_EXPRESSION_H

#include <iostream>

#define ASSIGN_EXPRESSION   "ASSIGN_EXPRESSION"
#define BINARY_EXPRESSION   "BINARY_EXPRESSION"
#define GROUP_EXPRESSION    "GROUP_EXPRESSION"
#define LITERAL_EXPRESSION  "LITERAL_EXPRESSION"
#define UNARY_EXPRESSION    "UNARY_EXPRESSION"
#define VARIABLE_EXPRESSION "VARIABLE_EXPRESSION"

class Expression {
    public:
        virtual ~Expression() = default;
        virtual std::string classType() = 0;
        virtual std::string toString() = 0;
};

#endif