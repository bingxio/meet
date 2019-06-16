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

#include "lexer.hpp"

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

        else if ((int) current == 39) lexString();

        else lexSymbol();
    }

    addToken(TOKEN_EOF, "EOF", 0);

    return this->tokens;
}

char Lexer::look() {
    return this->source.at(this->position);
}

char Lexer::look(int pos) {
    if (this->position + pos > (this->source.length() - 1))
        return '\0';
    else
        return this->source.at(this->position + pos);
}

bool Lexer::isAtEnd() {
    return (this->source.length() - 1) < this->position;
}

void Lexer::addToken(TokenType type) {
    addToken(type, false);
}

void Lexer::addToken(TokenType type, bool skipTwoPos) {
    if (skipTwoPos)
        addToken(type, look() + std::string(1, look(1)), 2);
    else
        addToken(type, std::string(1, look()), 1);
}

void Lexer::addToken(TokenType type, std::string literal, int skip) {
    if (type == TOKEN_EOF)
        this->tokens.emplace_back(type, literal, ++ this->line);
    else
        this->tokens.emplace_back(type, literal, this->line);

    if (skip) this->position += skip;
}

TokenType Lexer::isKeyword(std::string identifier) {
    std::map<std::string, TokenType>::iterator finded = this->keywords.find(identifier);

    if (finded != this->keywords.end())
        return finded->second;
    else
        return TOKEN_EOF;
}

void Lexer::lexIdentifier() {
    std::stringstream literalStream;

    while (isalpha(look())) {
        literalStream << look();

        if (isAtEnd())
            break;
        else
            this->position ++;
    }

    TokenType type = isKeyword(literalStream.str());

    addToken(type != TOKEN_EOF ? type : TOKEN_VALUE_IDENTIFIER, literalStream.str(), 1);
}

void Lexer::lexString() {
    std::stringstream literalStream;

    this->position ++;

    if (isAtEnd())
        throw std::runtime_error("syntax error: expect string lost right mark.");

    while (look() != '\'') {
        literalStream << look();

        if (isAtEnd())
            throw std::runtime_error("syntax error: expect string lost right mark.");
        else
            this->position ++;
    }

    addToken(TOKEN_VALUE_STRING, literalStream.str(), 1);
}

void Lexer::lexNumber() {
    std::stringstream literalStream;

    bool haveDot = false;

    while (isdigit(look()) || look() == '.') {
        literalStream << look();

        if (look() == '.')
            haveDot = true;

        if (isAtEnd())
            break;
        else
            this->position ++;
    }

    addToken(haveDot ? TOKEN_VALUE_FLOAT : TOKEN_VALUE_INT, literalStream.str(), 1);
}

void Lexer::lexSymbol() {
    switch (look()) {
        case '+':
            look(1) == '=' ? addToken(TOKEN_PLUS_EQUAL, true) : 
                addToken(TOKEN_PLUS, false);
            break;
        case '-':
            look(1) == '>' ? addToken(TOKEN_MINUS_GREATER, true) :
                look(1) == '=' ? addToken(TOKEN_MINUS_EQUAL, true) :
                    addToken(TOKEN_MINUS, false);
            break;
        case '*':
            look(1) == '=' ? addToken(TOKEN_STAR_EQUAL, true) :
                addToken(TOKEN_STAR, false);
            break;
        case '/':
            look(1) == '=' ? addToken(TOKEN_SLASH_EQUAL, true) :
                addToken(TOKEN_SLASH, false);
            break;
        case ';':
            addToken(TOKEN_SEMICOLON);
            break;
        case ':':
            addToken(TOKEN_COLON);
            break;
        case '.':
            addToken(TOKEN_DOT);
            break;
        case ',':
            addToken(TOKEN_COMMA);
            break;
        case '(':
            addToken(TOKEN_LPAREN);
            break;
        case ')':
            addToken(TOKEN_RPAREN);
            break;
        case '{':
            addToken(TOKEN_LBRACE);
            break;
        case '}':
            addToken(TOKEN_RBRACE);
            break;
        case '[':
            addToken(TOKEN_LBRACKET);
            break;
        case ']':
            addToken(TOKEN_RBRACKET);
            break;
        case '=':
            look(1) == '=' ? addToken(TOKEN_EQUAL_EQUAL, true) :
                addToken(TOKEN_EQUAL, false);
            break;
        case '!':
            look(1) == '=' ? addToken(TOKEN_BANG_EQUAL, true) :
                addToken(TOKEN_BANG, false);
            break;
        case '>':
            look(1) == '=' ? addToken(TOKEN_GREATER_EQUAL, true) :
                addToken(TOKEN_GREATER, false);
            break;
        case '<':
            look(1) == '=' ? addToken(TOKEN_LESS_EQUAL, true) :
                addToken(TOKEN_LESS, false);
            break;
        case '|':
            addToken(TOKEN_OR);
            break;
        case '&':
            addToken(TOKEN_AND);
            break;
        case '%':
            addToken(TOKEN_MODULAR);
            break;
        default:
            throw std::runtime_error("syntax error: unexpect character.");
    }
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
            while (look() != '\n' && !isAtEnd())
                this->position ++;
            this->position ++;
    }
}
