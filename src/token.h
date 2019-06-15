/**
 * Meet Programming Language Tokens.
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
#ifndef MEET_TOKEN_H
#define MEET_TOKEN_H

#include <iostream>

typedef std::string TokenType;

#define TOKEN_VALUE_INT
#define TOKEN_VALUE_FLOAT
#define TOKEN_VALUE_STRING
#define TOKEN_VALUE_BOOLEAN
#define TOKEN_VALUE_ANY

#define TOKEN_INT     "int"
#define TOKEN_FLOAT   "float"
#define TOKEN_STRING  "string"
#define TOKEN_BOOLEAN "boolean"
#define TOKEN_ANY     "any"

#define TOKEN_VAR     "var"

#define TOKEN_EOF     "EOF"

class Token {
    private:
        TokenType type;

        std::string literal;

        int line;
    public:
        explicit Token(TokenType type, std::string literal, int line);

        TokenType getTokenType();

        std::string getTokenLiteral();

        int getTokenLine();
};

#endif
