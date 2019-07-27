### 如何快速的实现一门编程语言

非常抱歉我在这次技术交流上由于自身原因导致分享不下去。我通过这篇文章给他家分享。

这个教程不会涉及 LLVM、Anltr、Yacc 等各种框架，而是从头开始写解析器和语法分析器，最后通过以 visitor 模式进行遍历求值。

[项目地址](https://github.com/Turaiiao/meet)

我的 blog 上也写了几篇关于编译原理方面的：[Turaiiao's Blog](https://blog.xyiio.cn/)

#### 为什么想做编程语言？

我觉得编程是很有趣的事情，雷军曾在毕业论文上写下 “愿意写一辈子程序，因为这就是我的兴趣。”，自己一步一步实现想要的功能真的很有意思。
创建一个属于自己的编程语言，能够有优美的语法、不做过多的特性、轻量级和完美的包管理实现。

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

