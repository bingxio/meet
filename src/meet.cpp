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
#include <string.h>

#include "meet.hpp"

using namespace std;

static void repl() {
    char* line = (char *) malloc(1024);

    while (true) {
        cout << "meet > ";

        cin >> line;

        if (strlen(line) != -1)
            run(line);
    }
}

void runFile(const char* path) {
    cout << path << endl;
}

void run(const char* source) {
    cout << source << endl;
}

int main(int argc, char** argv) {
    if (argc == 1)
        repl();
    else if (argc == 2)
        runFile(argv[1]);
    else
        cout << "usage: " << argv[0] << "[ .meet file path ]" << endl;
    return 0;
}