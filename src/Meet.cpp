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
#include <cstdlib>

#include "Lexer.hpp"
#include "Token.hpp"
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "Value.hpp"

using namespace std;

map<string, Value>* environment = new map<string, Value>();

bool isDebugMode = false;

static void partitionLine() {
    for (int i = 0; i < 92; i ++)
        cout << "-";
    cout << endl;
}

static void run(const string& source);

static void repl() {
    char* line = (char *) malloc(1024);

    cout << "\n\t Meet Programming Language 1.0.0 (debug mode, June 10 2019, 19:24) \n" << endl;

    while (true) {
        cout << "meet > ";

        cin.getline(line, 1024);

        if (strlen(line) == 0)
            continue;
        
        run(line);
    }
}

static void runFile(const char* path) {
    char* suffix = (char *) malloc(8);

    for (int i = 1; i < 6; i ++)
        suffix[i- 1] = path[strlen(path) - i];

    if (strcmp(suffix, "teem.") != 0) {
        cout << "read .meet file only." << endl;

        exit(64);
    }

    ifstream fileStream;

    fileStream.open(path);

    if (fileStream.fail()) {
        cerr << "cannot open file." << endl;

        exit(64);
    }

    string source((istreambuf_iterator<char>(fileStream)), (istreambuf_iterator<char>()));

    run(source);

    fileStream.close();

    delete suffix;
}

static void run(const string& source) {
    int i = 0;

    Lexer* lexer = new Lexer(source);

    vector<Token> tokens = lexer->tokenizer();

    if (isDebugMode) {
        for (auto token : tokens)
            printf("%-5d %-25s : %-50s : %5d \n", i ++, getTokenLiteralWithType(token.type).c_str(), 
                token.literal.c_str(), token.line);
        partitionLine();

        i = 0;
    }

    Parser* parser = new Parser(tokens);

    vector<Statement *> statements = parser->parseProgram();

    if (isDebugMode) {
        for (auto stmt : statements)
            printf("%-5d %-50s \n", i ++, stmt->toString().c_str());
        partitionLine();

        i = 0;
    }

    Interpreter* interpret = new Interpreter(statements, environment);

    interpret->execute();

    delete lexer;
    delete parser;
    delete interpret;

    if (isDebugMode) {
        for (auto obj : *environment)
            printf("%-5d %-25s : %s \n", i ++, obj.first.c_str(), obj.second.toString().c_str());
        partitionLine();

        i = 0;
    }
}

int main(int argc, char** argv) {
    if (argc == 1) repl();

    if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        isDebugMode = true;

        repl();

        return 0;
    }

    if (argc == 2) {
        runFile(argv[1]);

        return 0;
    }

    if (argc == 3 && strcmp(argv[2], "-d") == 0) {
        isDebugMode = true;

        runFile(argv[1]);

        return 0;
    }

    cout << "usage: " << argv[0] << " [ .meet file path ] " << endl;

    return 0;
}
