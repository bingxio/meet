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

#define EXPRESSION_ASSIGN   "EXPRESSION_ASSIGN"
#define EXPRESSION_BINARY   "EXPRESSION_BINARY"
#define EXPRESSION_GROUP    "EXPRESSION_GROUP"
#define EXPRESSION_LITERAL  "EXPRESSION_LITERAL"
#define EXPRESSION_UNARY    "EXPRESSION_UNARY"
#define EXPRESSION_VARIABLE "EXPRESSION_VARIABLE"
#define EXPRESSION_LOGICAL  "EXPRESSION_LOGICAL"
#define EXPRESSION_LIST     "EXPRESSION_LIST"
#define EXPRESSION_GET      "EXPRESSION_GET"
#define EXPRESSION_SET      "EXPRESSION_SET"
#define EXPRESSION_CALL     "EXPRESSION_CALL"

class Expression {
    public:
        virtual ~Expression() = default;
        
        virtual std::string defintion() = 0;

        virtual std::string toString() = 0;
};

#endif