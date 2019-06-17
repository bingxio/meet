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

#include <map>
#include <sstream>

#include "../Expression.hpp"
#include "../Statement.hpp"

class VarStatement: public Statement {
    private:
        std::string name;

        Expression* initializer;

        std::map<std::string, Expression *> list;
    public:
        VarStatement(std::string name, Expression* initializer): name(std::move(name)), 
            initializer(std::move(initializer)) {}

        VarStatement(std::map<std::string, Expression *> list) {
            list = std::move(list);
        }

        ~VarStatement() {
            delete &name;
            delete initializer;

            list.clear();

            std::map<std::string, Expression *>().swap(list);
        }

        std::string classType() {
            return "VarStatement";
        }

        std::string toString() {
            if (list.size()) {
                std::stringstream stream;

                stream << "[ VarStatement: list = ";

                for (auto i : list) {
                    stream << i.first << " -> ";
                    stream << i.second->toString() << " ";
                }

                stream << "]";

                return stream.str();
            }

            return "[ VarStatement: token = " + name + ", initializer = " + 
                initializer->toString() + " ]";
        }
};

#endif