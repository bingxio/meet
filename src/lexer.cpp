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

    this->keywords["int"]     = TOKEN_INT;
    this->keywords["float"]   = TOKEN_FLOAT;
    this->keywords["string"]  = TOKEN_STRING;
    this->keywords["boolean"] = TOKEN_BOOLEAN;
    this->keywords["list"]    = TOKEN_LIST;
    this->keywords["any"]     = TOKEN_ANY;
    this->keywords["null"]    = TOKEN_NULL;
    this->keywords["true"]    = TOKEN_TRUE;
    this->keywords["false"]   = TOKEN_FALSE;

    this->keywords["var"]      = TOKEN_VAR;
    this->keywords["or"]       = TOKEN_OR;
    this->keywords["and"]      = TOKEN_AND;
    this->keywords["import"]   = TOKEN_IMPORT;
    this->keywords["show"]     = TOKEN_SHOW;
    this->keywords["as"]       = TOKEN_AS;
    this->keywords["open"]     = TOKEN_OPEN;
    this->keywords["fun"]      = TOKEN_FUN;
    this->keywords["return"]   = TOKEN_RETURN;
    this->keywords["enum"]     = TOKEN_ENUM;
    this->keywords["data"]     = TOKEN_DATA;
    this->keywords["impl"]     = TOKEN_IMPL;
    this->keywords["if"]       = TOKEN_IF;
    this->keywords["elif"]     = TOKEN_ELIF;
    this->keywords["else"]     = TOKEN_ELSE;
    this->keywords["trait"]    = TOKEN_TRAIT;
    this->keywords["init"]     = TOKEN_INIT;
    this->keywords["this"]     = TOKEN_THIS;
    this->keywords["then"]     = TOKEN_THEN;
    this->keywords["override"] = TOKEN_OVERRIDE;
    this->keywords["new"]      = TOKEN_NEW;
    this->keywords["for"]      = TOKEN_FOR;
    this->keywords["while"]    = TOKEN_WHILE;
    this->keywords["match"]    = TOKEN_MATCH;
}

std::vector<Token> Lexer::tokenizer() {
    while (this->source.length() - 1 >= this->position) {
        char current = look();

        if (isspace(current) || current == '#')  lexSkipWriteSpace();

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
    if (this->position + pos > this->source.length() - 1)
        return '\0';
    else
        return this->source.at(this->position + pos);
}

bool Lexer::isAtEnd() {
    return this->source.length() - 1 <= this->position;
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
    this->tokens.emplace_back(type, literal, this->line);

    if (skip) 
        this->position += skip;
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

        if (isAtEnd()) {
            this->position ++;

            break;
        } else 
            this->position ++;
    }

    TokenType type = isKeyword(literalStream.str());

    addToken(type != TOKEN_EOF ? type : TOKEN_VALUE_IDENTIFIER, literalStream.str(), 0);
}

void Lexer::lexString() {
    std::stringstream literalStream;

    this->position ++;

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

        if (isAtEnd()) {
            this->position ++;

            break;
        } else
            this->position ++;
    }

    addToken(haveDot ? TOKEN_VALUE_FLOAT : TOKEN_VALUE_INT, literalStream.str(), 0);
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
    }
}
