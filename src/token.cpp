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
#include "token.h"

Token::Token(TokenType type, std::string literal, int line): literal(literal), line(line) {
    this -> type = type;
}

TokenType Token::getTokenType() {
    return this -> type;
}

std::string Token::getTokenLiteral() {
    return this -> literal;
}

int Token::getTokenLine() {
    return this -> line;
}