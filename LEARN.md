### 如何快速的实现一门编程语言

非常抱歉我在这次技术交流上由于自身原因导致分享不下去。我通过这篇文章给他家分享。

这个教程不会涉及 LLVM、Anltr、Yacc 等各种框架，而是从头开始写解析器和语法分析器，最后通过以 visitor 模式进行遍历求值。

[项目地址](https://github.com/Turaiiao/meet)

我的 blog 上也写了几篇关于编译原理方面的：[Turaiiao's Blog](https://blog.xyiio.cn/)

#### 为什么想做编程语言？

我觉得编程是很有趣的事情，雷军曾在毕业论文上写下 “愿意写一辈子程序，因为这就是我的兴趣。”，自己一步一步实现想要的功能真的很有意思。
创建一个属于自己的编程语言，能够有优美的语法、不做过多的特性、轻量级和完美的包管理实现，能应付简单的业务需求。

#### 实现什么？

我已经使用 C++ 实现了一些基本的语法结构，由于语言设计有很多缺陷，已经停止开发，后面准备用 Rust 进行重写并重订语法。

```
var a = 23, b = 0.5, c = 'hello world', d = false
var f: int = 34

println a
println a + b + f
println c + '123'
println d == true
println !d

var a: string = 'hello, ', b: string = 'world !'

println '$a $b'

if a > 20 & a < 25 -> println 'a > 20' else -> println 'a < 25'
if a > 20 {
    println 'a'
} elif a == 20 {
    println 'b'
} else {
    println 'c'
}

var a: list<int> = [ 1, 3, 4, 5, 6 ]
var b: list<any> = [ 1, 'a', false, 23, 4.5 ]

println a[0] + a[1] # 4
println b[0] + b[3] # 24
println b[1] + b[1] # "aa"

for var a = 0; a < 10; a += 1 -> println a

var a: int = 10

while a > 0 {
    if a % 2 == 0 ->
        println a
    a -= 1
}

# 例如生成一个心？

var x: float , y: float, str: string

for var i = 1.5; i > -1.5; i -= 0.1 {
    str = ''

    for x = -1.5; x < 1.5; x += 0.05 {
        y = x * x + i * i - 1

        if y * y * y - x * x * i * i * i < 0.0 ->
            str += '*'
        else -> 
            str += ' '
    }

    println str
}

# turaiiao@turaiiao-P45VJ:~/Desktop/meet$ ./meet ./test/heart.meet 
#                                                              
#                                                              
#                                                              
#                 *********           *********                
#             *****************   *****************            
#            ****************************************          
#          *******************************************         
#         *********************************************        
#         *********************************************        
#         *********************************************        
#         *********************************************        
#         *********************************************        
#         *********************************************        
#          *******************************************         
#           *****************************************          
#            ****************************************          
#             *************************************            
#              ***********************************             
#               *********************************              
#                 *****************************                
#                   *************************                  
#                     *********************                    
#                        ***************                       
#                           *********                          
#                              ***                             
#                     
#                                                              
# turaiiao@turaiiao-P45VJ:~/Desktop/meet$ 

fun a (a: int, b: int) -> int {
    return a + b
}

fun assign (a: string, b: string, c: boolean) {
    if c ->
        println '$a $b'
    else ->
        println 'undefined'
}

println a (1, 2)
println assign ('hello', 'world', true)

```

#### 有没有必要讲下编译器呢？

编译器（compiler）是一个能够把字符串编译成指定语言格式的程序。

例如，Ocmal、C/C++、Go、Python、Java、JavaScript、Haskell、PHP、Ruby、Erlang 都是编译型语言。
编译成字节码的语言也叫编译器，通过自己的虚拟机执行。

解释器（Interpreter）能够解释某个特定语法树和节点的程序。

例如 JLox、Monkey、VimScript、TypeScript、 等等的语言玩具。

本文将会讲解一个 Meet 的解释器。

#### 词法分析

编译器接受一个字符串，首先转换成词法列表，例如：

**可以加入 -d 参数展示词法列表、语法节点**

```
var a: int = 20

if a > 0 & a < 30 {
    println 'hello world'
}

# turaiiao@DESKTOP-AH5VM1I:~/meet/test$ ../meet ./test.meet -d
# 0     TOKEN_VAR                 : var                                                :     1
# 1     TOKEN_VALUE_IDENTIFIER    : a                                                  :     1
# 2     TOKEN_COLON               : :                                                  :     1
# 3     TOKEN_INT                 : int                                                :     1
# 4     TOKEN_EQUAL               : =                                                  :     1
# 5     TOKEN_VALUE_INT           : 20                                                 :     1
# 6     TOKEN_IF                  : if                                                 :     3
# 7     TOKEN_VALUE_IDENTIFIER    : a                                                  :     3
# 8     TOKEN_GREATER             : >                                                  :     3
# 9     TOKEN_VALUE_INT           : 0                                                  :     3
# 10    TOKEN_AND                 : &                                                  :     3
# 11    TOKEN_VALUE_IDENTIFIER    : a                                                  :     3
# 12    TOKEN_LESS                : <                                                  :     3
# 13    TOKEN_VALUE_INT           : 30                                                 :     3
# 14    TOKEN_LBRACE              : {                                                  :     3
# 15    TOKEN_PRINTLN             : println                                            :     4
# 16    TOKEN_VALUE_STRING        : hello world                                        :     4
# 17    TOKEN_RBRACE              : }                                                  :     5
# 18    TOKEN_EOF                 : EOF                                                :     6
# --------------------------------------------------------------------------------------------

hello world
```

[具体源码参考](https://github.com/Turaiiao/meet/blob/master/src/Lexer.cpp)

#### 语法分析

语法分析（Parser）我认为是最难的一个步骤，它考虑任意表达式的解析和复杂语法的解析，Lambda、等等。

传入之前解析的词法列表，一一匹配，都将转换成各种语法节点。

```
var a: int = 20, b: int = 30

if a > b -> println 'a greater than b'

println 1 + 2 * 3 - (4 + 5)

[ VarStatement: list = [ name = a, value = [ LiteralExpression: token = 20 ], type = int | name = b, value = [ LiteralExpression: token = 30 ], type = int | ]

[ IfStatement: condition = [ ExpressionStatement: expr = [ BinaryExpression: left = [ VariableExpression: name = a ], token = >, right = [ VariableExpression: name = b ] ] ], establish = [ BlockStatement: block = [ PrintlnStatement: expr = [ VariableExpression: name = a ], cls = true ] | , elifCondition = [ ExpressionStatement: expr = [ BinaryExpression: left = [ VariableExpression: name = a ], token = ==, right = [ VariableExpression: name = b ] ] ], elifEstablish = [ BlockStatement: block = [ PrintlnStatement: expr = [ VariableExpression: name = b ], cls = true ] | , elseEstablish = [ BlockStatement: block = [ PrintlnStatement: expr = [ BinaryExpression: left = [ VariableExpression: name = a ], token = +, right = [ VariableExpression: name = b ] ], cls = true ] |  ]

[ PrintlnStatement: expr = [ BinaryExpression: left = [ BinaryExpression: left = [ LiteralExpression: token = 1 ], token = +, right = [ BinaryExpression: left = [ LiteralExpression: token = 2 ], token = *, right = [ LiteralExpression: token = 3 ] ] ], token = -, right = [ GroupExpression: expr = [ BinaryExpression: left = [ LiteralExpression: token = 4 ], token = +, right = [ LiteralExpression: token = 5 ] ] ] ], cls = true ]

```

不好意思之前没有进行优化，直接挨着输出的所以不太美观。

可以看出，每个节点都有一个特定的名称，例如：

```
a、12、'abc' -> LiteralExpr

1 + 2 -> [ BinaryExpr = [ Left = LiteralExpr, Op = '+', Right = LiteralExpr ] ]

println a -> [ PrintlnStmt = [ Expr = LiteralExpr ] ]

if a + 1 -> println a

[ IfStmt = [ Condition = [ BinaryExpr... ], Block = [ PrintlnStmt = [ Expr = LiteralExpr ] ] ] ]
```

解析表达式比较麻烦，通常使用自顶向下分析法。依次遍历词法列表，直到遇到最高优先级符号结束。

自顶向下分析法参照 104 - 352 行。[Parser.cpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Parser.cpp#L104)

if, for, while, 等等的语法解析参照 Parser.cpp。

例如解析一个 while 语句：[Interpreter.cpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Parser.cpp#L486)

```c++
Statement* Parser::whileStatement() {
    WhileStatement* whileStatement = new WhileStatement;

    whileStatement->condition = statement();

    if (look(TOKEN_MINUS_GREATER))
        whileStatement->block = (BlockStatement *) minusGreaterBlockStatement();
    else if (look(TOKEN_LBRACE))
        whileStatement->block = (BlockStatement *) blockStatement();
    else
        error("syntax error: exepct '{' or '->' after while statement condition.");

    return whileStatement;
}
```

各种语法节点参照 expressions 和 statements 文件夹。

#### 符号表和运行环境

通常解释器存储运行时数据、例如变量等等。[Interpreter.hpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Interpreter.hpp#L59)

都是使用 map 这个数据结构存储，K 代表名字，V 代表内容。

我们只需要遍历一遍语法树就可以了。参照 82 行 [Interpreter.cpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Interpreter.cpp#L82)

map 里的 V 可以存储任意 Value，由此我定义了 Value.hpp 去存储各种类型。

[Value.hpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Value.hpp#L32)

例如输出节点的处理：[Interpreter.cpp](https://github.com/Turaiiao/meet/blob/master/src/interpreter/Interpreter.cpp#L528)

```c++
void Interpreter::executePrintlnStatement(Statement* stmt) {
    PrintlnStatement* printlnStmt = (PrintlnStatement *) stmt;

    Value a = executeExpression(printlnStmt->expression);

    if (printlnStmt->cls)
        a.printLineValue();
    else
        a.printValue();
}
```

#### 逆波兰表达式和栈、字节码

二元运算符总是置于与之相关的两个运算对象之间，这种表示法也称为中缀表示。
波兰逻辑学家 J.Lukasiewicz 于 1929 年提出了另一种表示表达式的方法，按此方法，每一运算符都置于其运算对象之后，故称为后缀表示。

```
1 + 2 * 3 - 4 -> 1 2 3 * + 4 -

OP_LOCAL    1
OP_LOCAL    2
OP_LOCAL    3
OP_MULTIPLY
OP_ADD
OP_LOCAL    4
OP_SUBTRACT
```

[解析函数](https://github.com/Turaiiao/stack-evaluate/blob/master/stack-four-operational-execute.rs#L50)

然后转换成一个块（Chunk），通常传送给虚拟机只是一个块，里面包括几个栈，运算栈、字节码栈等等。

```rust
struct Chunk {
    opcode_stack: Vec<OpCode>,
    values_stack: Vec<i32>
}

trait ChunkImpl {
    // emit a OP_LOCAL and some value to chunk.
    fn emit_constant(&mut self, value: i32);
    // only emit a opcode.
    fn emit_opcode(&mut self, opcode: OpCode);
    // display opcodes and values.
    // display value if it is OP_LOCAL else only opcode.
    fn display(&self);
}

fn transform(stack: Vec<char>) -> Chunk {
    let a: Vec<OpCode> = Vec::new();
    let b: Vec<i32> = Vec::new();

    let mut chunk = Chunk {
        opcode_stack: a,
        values_stack: b
    };

    for i in stack {
        match i {
            '0'..='9' => chunk.emit_constant(
                (i as i32) - 48
            ),

            '+' => chunk.emit_opcode(OpCode::OpAdd),
            '-' => chunk.emit_opcode(OpCode::OpSubtract),
            '*' => chunk.emit_opcode(OpCode::OpMultiply),
            '/' => chunk.emit_opcode(OpCode::OpDivide),

            _ => unimplemented!()
        }
    }

    chunk.emit_opcode(OpCode::OpReturn);

    return chunk;
}
```

然后一个 visitor 执行，遍历字节码栈，如果是 OP_LOCAL 就入运算栈，如果遇到 OP_ADD 就运算栈出栈两个值进行运算并把值压栈。

```rust
fn visitor(chunk: Chunk) {
    let mut stack: Vec<f32> = Vec::new();
    
    let mut k = 0;

    for i in chunk.opcode_stack {
        match i {
            OpCode::OpLocal => {
                stack.push(
                    *chunk.values_stack.get(k).unwrap() as f32
                );
                k += 1;
            }

            OpCode::OpReturn => break,

            _ => {
                let a = stack.pop().unwrap();
                let b = stack.pop().unwrap();

                match i {
                    OpCode::OpAdd => stack.push(b + a),
                    OpCode::OpSubtract => stack.push(b - a),
                    OpCode::OpMultiply => stack.push(b * a),
                    OpCode::OpDivide => stack.push(b / a),

                    _ => unimplemented!()
                }
            }
        }
    }

    println!("{:.6}", stack.last().unwrap());
}
```

#### CPython 字节码

我们知道 CPython 是使用纯 C 语言编写的。仅仅使用栈结构。

CPython 使用三种类型的栈：

- 调用栈（CallStack），这是主要结构，每个当前活动使用了一个叫 帧（Frame），栈底是程序入口，每当调用函数就推送一个帧到栈里，结束函数则销毁。
- 计算栈（EvaluationStack）在每个帧中有一个计算栈，大多数代码都是在这里运行，操作它们然后销毁它。
- 块栈（BlockStack）它用于追踪某些特定的接口，例如 break、continue、try、with 块等，这个帮助 Python 表示任意时刻哪个块是活动的，例如 continue 会影响正确的块。

Python 中可以引用 dis 模块进行字节码的反汇编然后输出。

```
>>> import dis
>>> def a():
...     print('Hello World')
...
>>> dis.dis(a)
  2           0 LOAD_GLOBAL              0 (print)
              2 LOAD_CONST               1 ('Hello World')
              4 CALL_FUNCTION            1
              6 POP_TOP
              8 LOAD_CONST               0 (None)
             10 RETURN_VALUE
>>> def a():
...     x = 2
...     y = 5
...     print(x + y)
...
>>> dis.dis(a)
  2           0 LOAD_CONST               1 (2)
              2 STORE_FAST               0 (x)

  3           4 LOAD_CONST               2 (5)
              6 STORE_FAST               1 (y)

  4           8 LOAD_GLOBAL              0 (print)
             10 LOAD_FAST                0 (x)
             12 LOAD_FAST                1 (y)
             14 BINARY_ADD
             16 CALL_FUNCTION            1
             18 POP_TOP
             20 LOAD_CONST               0 (None)
             22 RETURN_VALUE
```

我们可以很清楚的看到字节码和运行流程。

#### 更多参考

本人文笔不佳，以下教程可以对你更有帮助。

[munificent](https://github.com/munificent)
[craftinginterpreters](http://www.craftinginterpreters.com/)
[《自己动手实现 lua》](https://github.com/zxh0/luago-book)
