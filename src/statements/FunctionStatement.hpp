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
#ifndef MEET_FUNCTION_STATEMENT_H
#define MEET_FUNCTION_STATEMENT_H

#include "../Statement.hpp"
#include "../Token.hpp"

#include "BlockStatement.hpp"

class FunctionStatement: public Statement {
    public:
        Token name;

        std::map<std::string, std::string> parameters;

        BlockStatement* block;

        Token returnType;

        std::string defintion() {
            return STATEMENT_FUN;
        }

        std::string toString() {
            std::stringstream data;

            data << "[ FunctionStatement: name = " << name.literal << ", parameters size = ";

            data << parameters.size() << ", block = " << block->toString() << ", return = ";

            data << returnType.literal << " ]";

            return data.str();
        }
};

#endif