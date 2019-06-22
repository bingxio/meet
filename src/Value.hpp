/**
 * Meet Programming Language Values.
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
#ifndef MEET_VALUE_H
#define MEET_VALUE_H

#include <iostream>
#include <map>

#include "Token.hpp"

class Value {
    public:
        explicit Value(double value);
        explicit Value(std::string value);
        explicit Value(bool value);

        Value(); // Null value.

        Value operator + (const Value& a);
        Value operator - (const Value& b);
        Value operator * (const Value& b);
        Value operator / (const Value& b);
        Value operator % (const Value& b);
        Value operator > (const Value& b);
        Value operator < (const Value& b);
        Value operator >= (const Value& b);
        Value operator <= (const Value& b);
        Value operator != (const Value& b);
        Value operator == (const Value& b);
        Value operator || (const Value& b);
        Value operator && (const Value& b);

        bool valueNumber = false;
        bool valueString = false;
        bool valueBool = false;
        bool valueNull = false;

        double numberValue = 0;
        bool boolValue = false;
        std::string stringValue = std::string();

        void printValue();
        void printLineValue();
};

Value backValueWithToken(Token token);

#endif