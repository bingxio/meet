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
#ifndef MEET_VAR_STATEMENT
#define MEET_VAR_STATEMENT

#include <vector>
#include <sstream>

#include "../Statement.hpp"
#include "../expressions/AssignExpression.hpp"

class VarStatement: public Statement {
    public:
        std::vector<AssignExpression *> list;

        VarStatement(std::vector<AssignExpression *> list): list(std::move(list)) {}

        ~VarStatement() {
            list.clear();

            std::vector<AssignExpression *>().swap(list);
        }

        std::string defintion() {
            return STATEMENT_VAR;
        }

        std::string toString() {
            std::stringstream stream;

            stream << "[ VarStatement: list = [ ";

            for (auto i : list) {
                stream << "name = " << i->name.literal << ", value = ";

                if (i->initializer != nullptr)
                    stream << i->initializer->toString() << ", type = ";
                else
                    stream << "null, type = ";

                if (i->typed.literal.length() != 0)
                    stream << i->typed.literal << " | ";
                else
                    stream << "any" << " | ";
            }

            stream << "]";

            return stream.str();
        }
};

#endif