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
#include <sstream>

#include "lexer.h"

Lexer::Lexer(std::string source) {
    this->source = std::move(source);
    this->tokens = std::vector<Token>();
    this->line = 1;
    this->position = 0;

    this->keywords["var"] = TOKEN_VAR;
}

std::vector<Token> Lexer::tokenizer() {
    while (this->source.length() > this->position) {
        char current = look();

        if (isspace(current) || isblank(current) || current == '#')  lexSkipWriteSpace();

        else if (isalpha(current)) lexIdentifier();
        else if (isdigit(current)) lexNumber();

        else if (current = '\'') lexString();

        else lexSymbol();
    }

    addToken(TOKEN_EOF, "EOF", ++ this->line);

    return this->tokens;
}

char Lexer::look() {
    return this->source.at(this->position);
}

char Lexer::look(int pos) {
    if (this->position + pos > this->source.length())
        return '\0';
    else
        return this->source.at(this->position + pos);
}

bool Lexer::isAtEnd() {
    return this->source.length() <= this->position;
}

void Lexer::addToken(TokenType type, std::string literal, int line) {
    this->tokens.emplace_back(type, literal, line);
}

TokenType Lexer::isKeyword(std::string identifier) {
    std::map<std::string, TokenType>::iterator finded = this->keywords.find(identifier);

    if (finded != this->keywords.end())
        return finded->second;
    else
        return TOKEN_EOF;
}

void Lexer::lexIdentifier() {
    std::cout << "lex identifier" << std::endl;
}

void Lexer::lexString() {
    std::stringstream literalStream;

    this->position ++;

    while (look() != '\'') {
        literalStream << look();

        this->position ++;

        if (isAtEnd())
            throw std::runtime_error("syntax error: expect string lost right mark.");
    }

    this->position ++;

    addToken(TOKEN_VALUE_STRING, literalStream.str(), this->line);
}

void Lexer::lexNumber() {
    std::cout << "lex number" << std::endl;
}

void Lexer::lexSymbol() {
    std::cout << "lex symbol" << std::endl;
}

void Lexer::lexSkipWriteSpace() {
    switch (look()) {
        case ' ':
        case '\r':
        case '\t':
            this->position ++;
            break;
        case '\n':
            this->line ++;
            this->position ++;
            break;
        case '#':
            while (look(1) != '\n' && !isAtEnd())
                this->position ++;
    }
}
