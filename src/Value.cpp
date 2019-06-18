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
#include "Value.hpp"

Value::Value(double value) {
    this->valueNumber = true;
    this->numberValue = std::move(value);
}

Value::Value(std::string value) {
    this->valueString = true;
    this->stringValue = std::move(value);
}

Value::Value(bool value) {
    this->valueBool = true;
    this->boolValue = value;
}

void Value::setConstant(bool constant) {
    this->valueConstant = constant;
}

Value backValueWithToken(Token token) {
    if (token.type == TOKEN_VALUE_INT || token.type == TOKEN_VALUE_FLOAT)
        return Value(std::stod(token.literal));

    if (token.type == TOKEN_VALUE_STRING)
        return Value(token.literal);

    if (token.type == TOKEN_TRUE)
        return Value(true);

    if (token.type == TOKEN_FALSE)
        return Value(false);

    throw std::runtime_error("type error: unknow literal token decode to value.");
}