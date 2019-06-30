/**
 * Meet Programming Language Interpreter.
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
#include "Interpreter.hpp"

Interpreter::Interpreter(std::vector<Statement *> statements, std::map<std::string, Value>* environment) {
    this->statements = std::move(statements);
    this->environment = environment;
    this->size = this->statements.size();
    this->position = 0;
    this->replMode = replMode;
}

void Interpreter::assign(std::string name, Value value) {
    this->environment->insert(std::pair<std::string, Value>(name, value));
}

void Interpreter::reAssign(std::string name, Value value) {
    std::map<std::string, Value>::iterator a = this->environment->find(name);

    if (a == this->environment->end())
        throw std::runtime_error("interpret error: undefind variable '" + name + "'.");

    this->environment->erase(a);
    this->assign(name, value);
}

Value Interpreter::get(std::string name) {
    std::map<std::string, Value>::iterator a = this->environment->find(name);

    if (a == this->environment->end())
        throw std::runtime_error("interpret error: undefined variable: '" + name + "'.");

    return a->second;
}

bool Interpreter::haveObject(std::string name) {
    return this->environment->find(name) != this->environment->end();
}

Statement* Interpreter::look() {
    return this->statements.at(this->position);
}

int Interpreter::removeStatement(int pos) {
    std::vector<Statement *>::iterator a = this->statements.begin() + pos;

    if (a == this->statements.end())
        return 0;
    else {
        this->statements.erase(a);
        this->position --;

        return this->statements.size();
    }
}

void Interpreter::execute() {
    while (this->size) {
        executeStatement(look());

        this->size = removeStatement(this->position ++);
    }
}

void Interpreter::executeStatement(Statement* stmt) {
    if (stmt->defintion() == STATEMENT_EXPRESSION) executeExpressionStatement(stmt);
    if (stmt->defintion() == STATEMENT_VAR)        executeVarStatement(stmt);
    if (stmt->defintion() == STATEMENT_PRINTLN)    executePrintlnStatement(stmt);
    if (stmt->defintion() == STATEMENT_BLOCK)      executeBlockStatement(stmt);
    if (stmt->defintion() == STATEMENT_BREAK)      executeBreakStatement();
    if (stmt->defintion() == STATEMENT_CONTINUE)   executeContinueStatement();
    if (stmt->defintion() == STATEMENT_FOR)        executeForStatement(stmt);
    if (stmt->defintion() == STATEMENT_IF)         executeIfStatement(stmt);
    if (stmt->defintion() == STATEMENT_WHILE)      executeWhileStatement(stmt);
    if (stmt->defintion() == STATEMENT_FUN)        executeFunctionStatement(stmt);
    if (stmt->defintion() == STATEMENT_RETURN)     executeReturnStatement(stmt);
}

Value Interpreter::executeExpression(Expression* expr) {
    if (expr->defintion() == EXPRESSION_LITERAL)
        return executeLiteralExpression(expr);

    if (expr->defintion() == EXPRESSION_BINARY)
        return executeBinaryExpression(expr);

    if (expr->defintion() == EXPRESSION_GROUP)
        return executeGroupExpression(expr);

    if (expr->defintion() == EXPRESSION_UNARY)
        return executeUnaryExpression(expr);

    if (expr->defintion() == EXPRESSION_ASSIGN)
        return executeAssignExpression(expr);

    if (expr->defintion() == EXPRESSION_LOGICAL)
        return executeLogicalExpression(expr);

    if (expr->defintion() == EXPRESSION_VARIABLE)
        return executeVariableExpression(expr);

    if (expr->defintion() == EXPRESSION_GET)
        return executeGetExpression(expr);

    if (expr->defintion() == EXPRESSION_SET)
        return executeSetExpression(expr);

    if (expr->defintion() == EXPRESSION_CALL)
        return executeCallExpression(expr);

    throw std::runtime_error("interpret error: unknow expression '" + expr->defintion() + "'.");
}

Value Interpreter::executeLiteralExpression(Expression* expr) {
    Token token = ((LiteralExpression *) expr)->token;

    if (token.type == TOKEN_VALUE_STRING) {
        std::stringstream data;

        bool haveDollarString = false;

        for (int i = 0; i < token.literal.length(); ) {
            char c = token.literal.at(i);

            if (c == '$') {
                haveDollarString = true;

                i ++;

                continue;
            }

            if (c == '\\' && i < token.literal.length() - 1) {
                if (token.literal.at(i + 1) == 'n') {
                    data << '\n';

                    i += 2;

                    continue;
                }

                if (token.literal.at(i + 1) == 't') {
                    data << '\t';

                    i += 2;

                    continue;
                }
            }

            if (haveDollarString) {
                std::stringstream stream;

                while (isalpha(c) && i < token.literal.length()) {
                    stream << c;

                    if (i >= token.literal.length() - 1)
                        break;

                    c = token.literal.at(++ i);
                }

                if (stream.str().length() != 0) {
                    data << this->get(stream.str()).toString();

                    if (i == token.literal.length() - 1 && !isspace(token.literal.at(i)))
                        i ++;
                }

                haveDollarString = c == '$';

                continue;
            }

            data << c;

            i ++;
        }

        return Value(data.str());
    }

    return backValueWithToken(token);
}

Value Interpreter::executeBinaryExpression(Expression* expr) {
    BinaryExpression* a = (BinaryExpression *) expr;

    Value l = executeExpression(a->left);
    Value r = executeExpression(a->right);

    if (a->token.type == TOKEN_PLUS)          return l + r;
    if (a->token.type == TOKEN_MINUS)         return l - r;
    if (a->token.type == TOKEN_STAR)          return l * r;
    if (a->token.type == TOKEN_SLASH)         return l / r;
    if (a->token.type == TOKEN_MODULAR)       return l % r;
    if (a->token.type == TOKEN_GREATER)       return l > r;
    if (a->token.type == TOKEN_GREATER_EQUAL) return l >= r;
    if (a->token.type == TOKEN_LESS)          return l < r;
    if (a->token.type == TOKEN_LESS_EQUAL)    return l <= r;
    if (a->token.type == TOKEN_BANG_EQUAL)    return l != r;
    if (a->token.type == TOKEN_EQUAL_EQUAL)   return l == r;

    bool isIdentifierLeftName = ((LiteralExpression *) a->left)->token.type == TOKEN_VALUE_IDENTIFIER;

    if (isIdentifierLeftName) {
        std::string name = ((LiteralExpression *) a->left)->token.literal;

        if (a->token.type == TOKEN_PLUS_EQUAL) {
            this->reAssign(name, l + r);

            return l + r;
        }

        if (a->token.type == TOKEN_MINUS_EQUAL) {
            this->reAssign(name, l - r);

            return l -r;
        }

        if (a->token.type == TOKEN_STAR_EQUAL) {
            this->reAssign(name, l * r);

            return l * r;
        }

        if (a->token.type == TOKEN_SLASH_EQUAL) {
            this->reAssign(name, l / r);

            return l / r;
        }
    }

    throw std::runtime_error("interpret error: unknow operator for binary expression.");
}

Value Interpreter::executeGroupExpression(Expression* expr) {
    return executeExpression(((GroupExpression *) expr)->expression);
}

Value Interpreter::executeUnaryExpression(Expression* expr) {
    UnaryExpression* unaryExpr = (UnaryExpression *) expr;

    Value a = executeExpression(unaryExpr->expression);

    if (unaryExpr->token.type == TOKEN_BANG) {
        if (a.valueNumber)
            return Value(!a.numberValue);

        if (a.valueBool)
            return Value(!a.boolValue);

        throw std::runtime_error("interpret error: unknow operator for unary expression.");
    }

    if (unaryExpr->token.type == TOKEN_MINUS) {
        if (a.valueNumber)
            return Value(-a.numberValue);

        if (a.valueFloat)
            return Value(-a.floatValue);

        throw std::runtime_error("interpret error: unknow operator for unary expression.");
    }

    throw std::runtime_error("interpret error: unknow operator for unary expression.");
}

Value Interpreter::executeAssignExpression(Expression* expr) {
    AssignExpression* assignExpr = (AssignExpression *) expr;

    if (assignExpr->isVar && assignExpr->initializer == nullptr) {
        Value value = backValueWithNullTyped(assignExpr->typed.literal);

        this->assign(assignExpr->name.literal, value);

        return value;
    }

    if (assignExpr->initializer->defintion() == EXPRESSION_LIST) {
        ListExpression* listExpr = (ListExpression *) assignExpr->initializer;

        Value listValue = Value(listExpr->values);

        this->assign(assignExpr->name.literal, listValue);

        return listValue;
    }

    Value value = executeExpression(assignExpr->initializer);

    value.varAny = true;

    if (assignExpr->isVar) {
        if (this->haveObject(assignExpr->name.literal)) {
            throw std::runtime_error("interpret error: repeatedly defining variable '" + 
                assignExpr->name.literal + "'.");
        }

        if (assignExpr->typed.literal != "") {
            if (assignExpr->typed.literal == TOKEN_ANY)
                value.varAny = true;
            else if (assignExpr->typed.literal == TOKEN_INT && value.valueNumber)
                value.varNumber = true;
            else if (assignExpr->typed.literal == TOKEN_FLOAT && value.valueFloat)
                value.varFloat = true;
            else if (assignExpr->typed.literal == TOKEN_STRING && value.valueString)
                value.varString = true;
            else if (assignExpr->typed.literal == TOKEN_BOOLEAN && value.valueBool)
                value.varBoolean = true;

            if (!value.varNumber && !value.varFloat && !value.varString && !value.varBoolean && !value.varAny)
                throw std::runtime_error("interpret error: the value type is defferent from the specified.");
        }

        this->assign(assignExpr->name.literal, value);
    } else {
        Value a = this->get(assignExpr->name.literal);

        if ((a.varNumber && !value.valueNumber) || (a.varString && !value.valueString) ||
                (a.varBoolean && !value.valueBool) || (a.varFloat && !value.valueFloat)) {
            throw std::runtime_error("interpret error: cannot defined as other type.");
        }

        this->reAssign(assignExpr->name.literal, value);
    }

    return value;
}

Value Interpreter::executeLogicalExpression(Expression* expr) {
    LogicalExpression* logicalExpr = (LogicalExpression *) expr;

    Value a = executeExpression(logicalExpr->left);
    Value b = executeExpression(logicalExpr->right);

    if (logicalExpr->token.type == TOKEN_OR)
        return a || b;

    return a && b;
}

Value Interpreter::executeVariableExpression(Expression* expr) {
    VariableExpression* varExpr = (VariableExpression *) expr;

    return this->get(varExpr->name.literal);
}

Value Interpreter::executeGetExpression(Expression* expr) {
    GetExpression* getExpr = (GetExpression *) expr;

    Value value = executeExpression(getExpr->expression);

    if (getExpr->type == EXPRESSION_LIST) {
        if (value.valueNumber == false)
            throw std::runtime_error("interpret error: cannot use no number value to get array.");

        std::vector<Value> a = this->get(getExpr->name.literal).listValue;

        if (a.size() == 0 || value.numberValue > a.size() - 1)
            return Value();

        return a.at(value.numberValue);
    }

    return Value();
}

Value Interpreter::executeSetExpression(Expression* expr) {
    SetExpression* setExpr = (SetExpression *) expr;

    if (setExpr->type == EXPRESSION_LIST) {
        Value initializer = executeExpression(setExpr->expression);

        if (initializer.valueNumber == false)
            throw std::runtime_error("interpret error: cannot use no number value to get array.");

        std::vector<Value> a = this->get(setExpr->name.literal).listValue;

        Value value = executeExpression(setExpr->value);

        if (a.size() == 0 || initializer.numberValue > a.size() - 1)
            a.push_back(value);
        else
            a.at(initializer.numberValue) = value;

        this->reAssign(setExpr->name.literal, Value(a));

        if (setExpr->then != nullptr)
            executeStatement(setExpr->then);

        return value;
    }

    return Value();
}

/**
 * map<string -> name, string -> value>  : FunctionStatement Parameters.
 * vector<Value>                         : CallExpression Parameters.
 */
Value Interpreter::executeCallExpression(Expression* expr) {
    CallExpression* callExpr = (CallExpression *) expr;

    Value a = this->get(callExpr->name.literal);

    if (a.valueFun == false)
        throw std::runtime_error("interpret error: name '" + callExpr->name.literal + "' is not a function.");

    if (a.funValue->parameters.size() != callExpr->parameters.size())
        throw std::runtime_error("interpret error: inconsistency of real parameters.");

    int l = 0;

    std::map<std::string, Value> backup = std::map<std::string, Value>();

    for (std::map<std::string, std::string>::iterator i = a.funValue->parameters.begin();
            i != a.funValue->parameters.end(); i ++) {
        Value b = executeExpression(callExpr->parameters.at(l));

        if (i->second == TOKEN_STRING && !b.valueString)
            throw std::runtime_error("interpret error: function string argument type error.");
        else if (i->second == TOKEN_INT && !b.valueNumber)
            throw std::runtime_error("interpret error: function int argument type error.");
        else if (i->second == TOKEN_FLOAT && !b.valueFloat)
            throw std::runtime_error("interpret error: function float argument type error.");
        else if (i->second == TOKEN_BOOLEAN && !b.valueBool)
            throw std::runtime_error("interpret error: function boolean argument type error.");
        else if (i->second == TOKEN_LIST && !b.valueList)
            throw std::runtime_error("interpret error: function list argument type error.");

        if (i->second != TOKEN_STRING && i->second != TOKEN_INT && i->second != TOKEN_FLOAT &&
                i->second != TOKEN_BOOLEAN && i->second != TOKEN_LIST && this->haveObject(i->second) == false) {
            throw std::runtime_error("interpret error: undefind object name '" + i->second + "'.");
        }

        if (this->haveObject(i->first)) {
            backup.insert(std::pair<std::string, Value>(i->first, this->get(i->first)));

            this->reAssign(i->first, b);
        } else
            this->assign(i->first, b);

        l ++;
    }

    try {
        executeBlockStatement(a.funValue->block);
    } catch (ReturnStatement* operation) {
        Value v = executeExpression(operation->expression);

        if ((a.funValue->returnType.type == TOKEN_INT && !v.valueNumber) &&
            (a.funValue->returnType.type == TOKEN_FLOAT && !v.valueFloat) &&
            (a.funValue->returnType.type == TOKEN_STRING && !v.valueString) &&
            (a.funValue->returnType.type == TOKEN_BOOLEAN && !v.valueBool) &&
            (a.funValue->returnType.type == TOKEN_LIST && !v.valueList)) {

                if (this->haveObject(a.funValue->returnType.literal) == false)
                    throw std::runtime_error("interpret error: return type is different from defintion.");
            }

        for (auto i : a.funValue->parameters)
            this->environment->erase(i.first);

        if (backup.size() != 0) {
            for (auto i : backup) {
                this->assign(i.first, i.second);
            }
        }

        return v;
    }

    for (auto i : a.funValue->parameters)
        this->environment->erase(i.first);

    if (backup.size() != 0) {
        for (auto i : backup) {
            this->assign(i.first, i.second);
        }
    }

    return Value();
}

Value Interpreter::executeExpressionStatement(Statement* stmt) {
    return executeExpression(((ExpressionStatement *) stmt)->expression);
}

void Interpreter::executeVarStatement(Statement* stmt) {
    VarStatement* varStmt = (VarStatement *) stmt;

    for (auto i : varStmt->list)
        executeExpression(i);
}

void Interpreter::executePrintlnStatement(Statement* stmt) {
    PrintlnStatement* printlnStmt = (PrintlnStatement *) stmt;

    Value a = executeExpression(printlnStmt->expression);

    if (printlnStmt->cls)
        a.printLineValue();
    else
        a.printValue();
}

void Interpreter::executeBlockStatement(Statement* stmt) {
    BlockStatement* blockStmt = (BlockStatement *) stmt;

    std::map<std::string, Value>* old = new std::map<std::string, Value>();

    old->insert(this->environment->begin(), this->environment->end());

    for (auto i : blockStmt->block)
        executeStatement(i);

    for (auto i : *this->environment) {
        std::map<std::string, Value>::iterator name = old->find(i.first);

        if (name == old->end()) {
            auto a = this->environment->find(i.first);

            this->environment->erase(a);
        }
    }

    delete old;
}

std::vector<std::string> Interpreter::executeStatementWithoutEnvironment(Statement* stmt) {
    std::map<std::string, Value>* old = new std::map<std::string, Value>();

    std::vector<std::string> names = std::vector<std::string>();

    old->insert(this->environment->begin(), this->environment->end());

    executeStatement(stmt);

    for (auto i : *this->environment) {
        std::map<std::string, Value>::iterator name = old->find(i.first);

        if (name == old->end()) {
            names.push_back(i.first);
        }
    }

    delete old;

    return names;
}

void Interpreter::executeBreakStatement() {
    throw BreakStatement();
}

void Interpreter::executeContinueStatement() {
    throw ContinueStatement();
}

void Interpreter::executeForStatement(Statement* stmt) {
    ForStatement* forStmt = (ForStatement *) stmt;

    std::vector<std::string> names = executeStatementWithoutEnvironment(forStmt->initializer);

    Value condition = executeExpressionStatement(forStmt->condition);

    while (condition.boolValue) {
        try {
            executeBlockStatement(forStmt->block);
        } catch (BreakStatement operation) {
            break;
        } catch (ContinueStatement operation) {
            executeStatement(forStmt->renovate);

            condition = executeExpressionStatement(forStmt->condition);

            continue;
        }

        executeStatement(forStmt->renovate);

        condition = executeExpressionStatement(forStmt->condition);
    }

    for (int i = 0; i < names.size(); i ++) {
        this->environment->erase(this->environment->find(names.at(i)));
    }
}

void Interpreter::executeIfStatement(Statement* stmt) {
    IfStatement* ifStmt = (IfStatement *) stmt;

    bool condition = executeExpressionStatement(ifStmt->condition).boolValue;

    if (condition) {
        if (ifStmt->establish != nullptr)
            executeBlockStatement(ifStmt->establish);
        return;
    } else if (condition == false) {
        if (ifStmt->elifCondition != nullptr) {
            bool elifCondition = executeExpressionStatement(ifStmt->elifCondition).boolValue;

            if (elifCondition) {
                executeBlockStatement(ifStmt->elifEstablish);

                return;
            } else if (elifCondition == false && ifStmt->elseEstablish != nullptr) {
                executeBlockStatement(ifStmt->elseEstablish);

                return;
            }
        }

        if (ifStmt->elseEstablish != nullptr)
            executeBlockStatement(ifStmt->elseEstablish);
    }
}

void Interpreter::executeWhileStatement(Statement* stmt) {
    WhileStatement* whileStmt = (WhileStatement *) stmt;

    bool condition = executeExpressionStatement(whileStmt->condition).boolValue;

    while (condition) {
        try {
            executeBlockStatement(whileStmt->block);
        } catch (BreakStatement operation) {
            break;
        } catch (ContinueStatement operation) {
            condition = executeExpressionStatement(whileStmt->condition).boolValue;

            continue;
        }

        condition = executeExpressionStatement(whileStmt->condition).boolValue;
    }
}

void Interpreter::executeFunctionStatement(Statement* stmt) {
    FunctionStatement* funStmt = (FunctionStatement *) stmt;

    this->assign(funStmt->name.literal, Value(funStmt));
}

void Interpreter::executeReturnStatement(Statement* stmt) {
    throw (ReturnStatement *) stmt;
}