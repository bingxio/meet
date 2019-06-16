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
#ifndef MEET_LEXER_H
#define MEET_LEXER_H

#include <iostream>
#include <vector>
#include <map>

#include "token.hpp"

class Lexer {
    private:
        std::string source;
        std::vector<Token> tokens;
        std::map<std::string, TokenType> keywords;

        int line;
        int position;

        char look();
        char look(int pos);

        bool isAtEnd();

        TokenType isKeyword(std::string identifier);

        void addToken(TokenType type);
        void addToken(TokenType type, bool skipTwoPos);
        void addToken(TokenType type, std::string literal, int skip);

        void lexIdentifier();
        void lexString();
        void lexNumber();
        void lexSymbol();
        void lexSkipWriteSpace();
    public:
        Lexer(std::string source);

        std::vector<Token> tokenizer();
};

#endif
