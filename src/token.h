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

#define TOKEN_LPAREN        "("
#define TOKEN_RPAREN        ")"
#define TOKEN_LBRACE        "{"
#define TOKEN_RBRACE        "}"
#define TOKEN_LBRACKET      "["
#define TOKEN_RBRACKET      "]"
#define TOKEN_PLUS          "+"
#define TOKEN_MINUS         "-"
#define TOKEN_STAR          "*"
#define TOKEN_SLASH         "/"
#define TOKEN_EQUAL         "="
#define TOKEN_EQUAL_EQUAL   "=="
#define TOKEN_BANG          "!"
#define TOKEN_BANG_EQUAL    "!="
#define TOKEN_LESS          "<"
#define TOKEN_LESS_EQUAL    "<="
#define TOKEN_GREATER       ">"
#define TOKEN_GREATER_EQUAL ">="
#define TOKEN_PLUS_EQUAL    "+="
#define TOKEN_MINUS_EQUAL   "-="
#define TOKEN_STAR_EQUAL    "*="
#define TOKEN_SLASH_EQUAL   "/="
#define TOKEN_MODULAR       "%"
#define TOKEN_DOT           "."
#define TOKEN_COMMA         ","
#define TOKEN_SEMICOLON     ";"
#define TOKEN_MARK          "'"
#define TOKEN_COLON         ":"
#define TOKEN_MINUS_GREATER "->"

#define TOKEN_VALUE_INT         ""
#define TOKEN_VALUE_FLOAT       ""
#define TOKEN_VALUE_STRING      ""
#define TOKEN_VALUE_IDENTIFIER  ""

#define TOKEN_INT      "int"
#define TOKEN_FLOAT    "float"
#define TOKEN_STRING   "string"
#define TOKEN_BOOLEAN  "boolean"
#define TOKEN_LIST     "list"
#define TOKEN_ANY      "any"
#define TOKEN_NULL     "null"
#define TOKEN_TRUE     "true"
#define TOKEN_FALSE    "false"

#define TOKEN_VAR      "var"
#define TOKEN_OR       "or"
#define TOKEN_AND      "and"
#define TOKEN_IMPORT   "import"
#define TOKEN_SHOW     "show"
#define TOKEN_AS       "as"
#define TOKEN_OPEN     "open"
#define TOKEN_FUN      "fun"
#define TOKEN_RETURN   "return"
#define TOKEN_ENUM     "enum"
#define TOKEN_DATA     "data"
#define TOKEN_IMPL     "impl"
#define TOKEN_IF       "if"
#define TOKEN_ELIF     "elif"
#define TOKEN_ELSE     "else"
#define TOKEN_TRAIT    "trait"
#define TOKEN_INIT     "init"
#define TOKEN_THIS     "this"
#define TOKEN_THEN     "then"
#define TOKEN_OVERRIDE "override"
#define TOKEN_NEW      "new"
#define TOKEN_FOR      "for"
#define TOKEN_WHILE    "while"
#define TOKEN_MATCH    "match"

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

std::string getTokenLiteralWithType(TokenType tokenType);

#endif
