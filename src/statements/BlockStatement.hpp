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
#ifndef MEET_BLOCK_STATEMENT_H
#define MEET_BLOCK_STATEMENT_H

#include <vector>
#include <sstream>

#include "../Statement.hpp"

class BlockStatement: public Statement {
    public:
        std::vector<Statement *> block;

        BlockStatement(std::vector<Statement *> block): block(std::move(block)) {}

        ~BlockStatement() {
            block.clear();

            std::vector<Statement *>().swap(block);
        }

        std::string defintion() {
            return STATEMENT_BLOCK;
        }

        std::string toString() {
            std::stringstream data;

            data << "[ BlockStatement: block = ";

            for (auto i : block)
                data << i->toString() << " | ";

            return data.str();
        }
};

#endif