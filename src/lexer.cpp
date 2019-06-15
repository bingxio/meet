/**
 * Meet Programming Language Lexer.
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
#include <iostream>

#include "lexer.h"

Lexer::Lexer(std::string source) {
    this->source = std::move(source);
    this->tokens = std::vector<Token>();
    this->position = 0;

    this->keywords["var"] = TOKEN_VAR;
}

std::vector<Token> Lexer::tokenizer() {
    while (this->source.length() > this->position) {
        char current = look(0);

        std::cout << current << std::endl;

        this->position ++;
    }

    return this->tokens;
}

char Lexer::look(int pos) {
    if (this->position + pos > this->source.length())
        return '\0';
    else
        return this->source.at(this->position + pos);
}

void Lexer::addToken(Token token) {
    this->tokens.emplace_back(token);
}

TokenType Lexer::isKeyword(std::string identifier) {
    return TOKEN_EOF;
}

void Lexer::lexIdentifier() {

}

void Lexer::lexString() {

}

void Lexer::lexNumber() {

}

void Lexer::lexComment() {

}

void Lexer::lexWriteSpace() {

}
