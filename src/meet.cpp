/**
 * Meet Programming Language Main.
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
#include <fstream>
#include <cstring>
#include <cstdio>

#include "Lexer.hpp"
#include "Token.hpp"
#include "Common.hpp"
#include "Parser.hpp"

using namespace std;

static void run(const string& source);

static void repl() {
    char* line = (char *) malloc(1024);

    cout << "\n\t Meet Programming Language 1.0.0 (debug, June 10 2019, 19:24) \n" << endl;

    while (true) {
        cout << "meet > ";

        cin.getline(line, 1024);

        bool haveWriteSpace = false;

        for (int i = 0; i < strlen(line); i ++)
            haveWriteSpace = line[i] == 32;

        if (haveWriteSpace || line[0] == '\0')
            continue;
        
        run(line);
    }
}

static void runFile(const char* path) {
    ifstream fileStream;

    fileStream.open(path);

    if (fileStream.fail()) {
        cerr << "cannot open file." << endl;

        exit(64);
    }

    string source((istreambuf_iterator<char>(fileStream)), (istreambuf_iterator<char>()));

    run(source);

    fileStream.close();
}

static void run(const string& source) {
    int i = 0;

    Lexer* lexer = new Lexer(source);

    vector<Token> tokens = lexer->tokenizer();

#ifdef DEBUG_LEXER
    for (auto token : tokens)
        printf("token: %5d %-25s : %-50s : %5d \n", i ++, 
            getTokenLiteralWithType(token.getTokenType()).c_str(), token.getTokenLiteral().c_str(), 
                token.getTokenLine());
    i = 0;
#endif

    Parser* parser = new Parser(tokens);

    vector<Statement> statements = parser->parseProgram();

#ifdef DEBUG_PARSE
    // for (auto stmt : statements)
    //     printf("statement: %5d : %-50s \n", i ++, stmt.toString());
    i = 0;
#endif

    delete lexer;
    delete parser;
}

int main(int argc, char** argv) {
    if (argc == 1)
        repl();
    else if (argc == 2)
        runFile(argv[1]);
    else
        cout << "usage: " << argv[0] << " [ .meet file path ] " << endl;
    return 0;
}
