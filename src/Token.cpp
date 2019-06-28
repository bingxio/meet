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
#include <utility>

#include "Token.hpp"

Token::Token() {}

Token::Token(TokenType type, std::string literal, int line): literal(std::move(literal)), line(line) {
    this->type = std::move(type);
}

bool isTyped(const Token& token) {
    return token.type == TOKEN_INT || token.type == TOKEN_STRING || token.type == TOKEN_FLOAT ||
        token.type == TOKEN_LIST || token.type == TOKEN_BOOLEAN || token.type == TOKEN_ANY;
}

bool Token::operator < (Token token) const {
    return true;
}

std::string getTokenLiteralWithType(const TokenType& tokenType) {
    if (tokenType == TOKEN_LPAREN)           return "TOKEN_LPAREN";
    if (tokenType == TOKEN_RPAREN)           return "TOKEN_RPAREN";
    if (tokenType == TOKEN_LBRACE)           return "TOKEN_LBRACE";
    if (tokenType == TOKEN_RBRACE)           return "TOKEN_RBRACE";
    if (tokenType == TOKEN_LBRACKET)         return "TOKEN_LBRACKET";
    if (tokenType == TOKEN_RBRACKET)         return "TOKEN_RBRACKET";
    if (tokenType == TOKEN_PLUS)             return "TOKEN_PLUS";
    if (tokenType == TOKEN_MINUS)            return "TOKEN_MINUS";
    if (tokenType == TOKEN_STAR)             return "TOKEN_STAR";
    if (tokenType == TOKEN_SLASH)            return "TOKEN_SLASH";
    if (tokenType == TOKEN_EQUAL)            return "TOKEN_EQUAL";
    if (tokenType == TOKEN_EQUAL_EQUAL)      return "TOKEN_EQUAL_EQUAL";
    if (tokenType == TOKEN_BANG)             return "TOKEN_BANG";
    if (tokenType == TOKEN_BANG_EQUAL)       return "TOKEN_BANG_EQUAL";
    if (tokenType == TOKEN_LESS)             return "TOKEN_LESS";
    if (tokenType == TOKEN_LESS_EQUAL)       return "TOKEN_LESS_EQUAL";
    if (tokenType == TOKEN_GREATER)          return "TOKEN_GREATER";
    if (tokenType == TOKEN_GREATER_EQUAL)    return "TOKEN_GREATER_EQUAL";
    if (tokenType == TOKEN_PLUS_EQUAL)       return "TOKEN_PLUS_EQUAL";
    if (tokenType == TOKEN_MINUS_EQUAL)      return "TOKEN_MINUS_EQUAL";
    if (tokenType == TOKEN_STAR_EQUAL)       return "TOKEN_STAR_EQUAL";
    if (tokenType == TOKEN_SLASH_EQUAL)      return "TOKEN_SLASH_EQUAL";
    if (tokenType == TOKEN_MODULAR)          return "TOKEN_MODULAR";
    if (tokenType == TOKEN_DOT)              return "TOKEN_DOT";
    if (tokenType == TOKEN_COMMA)            return "TOKEN_COMMA";
    if (tokenType == TOKEN_SEMICOLON)        return "TOKEN_SEMICOLON";
    if (tokenType == TOKEN_MARK)             return "TOKEN_MARK";
    if (tokenType == TOKEN_COLON)            return "TOKEN_COLON";
    if (tokenType == TOKEN_MINUS_GREATER)    return "TOKEN_MINUS_GREATER";
    if (tokenType == TOKEN_DOLLAR)           return "TOKEN_DOLLAR";
    if (tokenType == TOKEN_VALUE_INT)        return "TOKEN_VALUE_INT";
    if (tokenType == TOKEN_VALUE_FLOAT)      return "TOKEN_VALUE_FLOAT";
    if (tokenType == TOKEN_VALUE_STRING)     return "TOKEN_VALUE_STRING";
    if (tokenType == TOKEN_VALUE_IDENTIFIER) return "TOKEN_VALUE_IDENTIFIER";
    if (tokenType == TOKEN_INT)              return "TOKEN_INT";
    if (tokenType == TOKEN_FLOAT)            return "TOKEN_FLOAT";
    if (tokenType == TOKEN_STRING)           return "TOKEN_STRING";
    if (tokenType == TOKEN_BOOLEAN)          return "TOKEN_BOOLEAN";
    if (tokenType == TOKEN_LIST)             return "TOKEN_LIST";
    if (tokenType == TOKEN_ANY)              return "TOKEN_ANY";
    if (tokenType == TOKEN_NULL)             return "TOKEN_NULL";
    if (tokenType == TOKEN_TRUE)             return "TOKEN_TRUE";
    if (tokenType == TOKEN_FALSE)            return "TOKEN_FALSE";
    if (tokenType == TOKEN_VAR)              return "TOKEN_VAR";
    if (tokenType == TOKEN_OR)               return "TOKEN_OR";
    if (tokenType == TOKEN_AND)              return "TOKEN_AND";
    if (tokenType == TOKEN_IMPORT)           return "TOKEN_IMPORT";
    if (tokenType == TOKEN_SHOW)             return "TOKEN_SHOW";
    if (tokenType == TOKEN_AS)               return "TOKEN_AS";
    if (tokenType == TOKEN_OPEN)             return "TOKEN_OPEN";
    if (tokenType == TOKEN_FUN)              return "TOKEN_FUN";
    if (tokenType == TOKEN_RETURN)           return "TOKEN_RETURN";
    if (tokenType == TOKEN_ENUM)             return "TOKEN_ENUM";
    if (tokenType == TOKEN_DATA)             return "TOKEN_DATA";
    if (tokenType == TOKEN_IMPL)             return "TOKEN_IMPL";
    if (tokenType == TOKEN_IF)               return "TOKEN_IF";
    if (tokenType == TOKEN_ELIF)             return "TOKEN_ELIF";
    if (tokenType == TOKEN_ELSE)             return "TOKEN_ELSE";
    if (tokenType == TOKEN_TRAIT)            return "TOKEN_TRAIT";
    if (tokenType == TOKEN_INIT)             return "TOKEN_INIT";
    if (tokenType == TOKEN_THIS)             return "TOKEN_THIS";
    if (tokenType == TOKEN_THEN)             return "TOKEN_THEN";
    if (tokenType == TOKEN_OVERRIDE)         return "TOKEN_OVERRIDE";
    if (tokenType == TOKEN_NEW)              return "TOKEN_NEW";
    if (tokenType == TOKEN_FOR)              return "TOKEN_FOR";
    if (tokenType == TOKEN_WHILE)            return "TOKEN_WHILE";
    if (tokenType == TOKEN_MATCH)            return "TOKEN_MATCH";
    if (tokenType == TOKEN_PRINTLN)          return "TOKEN_PRINTLN";
    if (tokenType == TOKEN_PRINT)            return "TOKEN_PRINT";
    if (tokenType == TOKEN_BREAK)            return "TOKEN_BREAK";
    if (tokenType == TOKEN_CONTINUE)         return "TOKEN_CONTINUE";
    if (tokenType == TOKEN_EOF)              return "TOKEN_EOF";

    return "UNKNOWN";
}