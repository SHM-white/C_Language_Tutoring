# [C **基础语法**](https://www.runoob.com/cprogramming/c-basic-syntax.html)

C 语言是一种通用的编程语言，广泛应用于系统编程、嵌入式开发和高性能计算等领域。

C 语言具有高效、灵活、可移植性强等特点，是许多其他编程语言的基础。

在 C 语言中，令牌（Token）是程序的基本组成单位，编译器通过对源代码进行词法分析，将代码分解成一个个的令牌。

C 语言的令牌主要包括以下几种类型：

* **关键字（Keywords）**
* **标识符（Identifiers）**
* **常量（Constants）**
* **字符串字面量（String Literals）**
* **运算符（Operators）**
* **分隔符（Separators）**

## C 程序的基本结构

这是一个简单的 C 语言程序，可以输出 "Hello, World!"：

## 实例
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```
以上代码组成结构如下：

* **预处理器指令** ：如 `#include` 和 `#define`。
* **主函数** ：每个 C 程序都有一个 `main()` 函数。
* **变量声明** ：声明程序中使用的变量。
* **函数定义** ：定义程序中使用的函数。

更复杂一点的 C 程序结构说明（后面章节会对每个知识点展开说明）：

## 实例
```c
#include <stdio.h>   // 头文件包含

#define PI 3.14159    // 宏定义

// 函数声明
int add(int a, int b);

int main() {         // 主函数
    // 变量声明
    int num1, num2, sum;

    // 用户输入
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    // 函数调用
    sum = add(num1, num2);

    // 输出结果
    printf("Sum: %d\n", sum);

    return 0;        // 返回 0 表示程序成功执行
}

// 函数定义
int add(int a, int b) {
    return a + b;
}
```
**头文件包含**

* 头文件通常在程序的开头使用 `#include` 指令包含。头文件提供了函数和库的声明，如标准输入输出库 `<stdio.h>`、标准库 `<stdlib.h>` 等。它们定义了函数、宏、常量等使程序能够使用预定义的库函数。
* 示例：`#include <stdio.h>`

**宏定义**

* 宏是通过 `#define` 指令定义的符号常量或代码片段。宏在编译前由预处理器替换为其定义的内容。常用于定义常量或者复杂的代码块。
* 示例：`#define PI 3.14159`

**函数声明**

* 在 C 语言中，函数的声明必须在函数定义或调用之前。声明提供了函数的返回类型、函数名和参数列表，以便编译器知道如何调用该函数。
* 示例：`int add(int a, int b);`

**主函数**

* `main()` 函数是 C 程序的入口点，每个 C 程序都必须包含一个 `main()` 函数。程序从 `main()` 开始执行，返回值通常为 `0` 表示程序成功执行。
* 示例：`int main() { ... }`

**变量声明**

* 在 C 程序中，所有变量必须在使用前声明。变量可以在 `main()` 函数中声明，也可以在其他函数中或全局声明。
* 示例：
  ```c
  printf("Enter two integers: ");
  sum = add(num1, num2);
  ```

**语句和表达式**

* 语句是 C 程序的基本执行单元，通常是函数调用、赋值、控制语句（如 `if`、`for` 等）或表达式。表达式是由变量、操作符和常量组成的代码片段。
* 示例：
  ```c
  printf("Enter two integers: ");
  sum = add(num1, num2);
  ```

**控制流语句**

* 控制流语句用于控制程序执行的顺序，包括 `if`、`for`、`while`、`do-while` 等循环和条件分支语句。
* 示例：
  ```c
  if(num1 > num2){
      printf("num1 is greater than num2");
  }
  ```

**函数定义**

* 函数定义包含实际的函数体，它描述了函数的具体实现。函数通常包含参数、局部变量和返回值。
* 示例：
  ```c
  int add(int a,int b){
      return a + b;
  }
  ```

**返回语句**

* `return` 语句用于终止函数的执行，并将控制权交还给调用函数。`main()` 函数的返回值通常是 `0` 表示正常执行。
* 示例：`return 0;`

## 分隔符

分隔符用于分隔语句和表达式，常见的分隔符包括：

* **逗号 **,** ** ：用于分隔变量声明或函数参数。
* **分号 **;** ** ：用于结束语句。
* **括号** ：
* 圆括号 `()` 用于分组表达式、函数调用。
* 花括号 `{}` 用于定义代码块。
* 方括号 `[]` 用于数组下标。

在 C 程序中，分号 **;** 是语句结束符，也就是说，每个语句必须以分号结束，它表明一个逻辑实体的结束。

例如，下面是两个不同的语句：

```c
printf("Hello, World! \n");
return 0;
```

个单独的分号也可以作为一个空语句，表示什么都不做。例如：

```c
;
```

## 注释

**C 语言有两种注释方式：**

```c
// 单行注释
```

以 **//** 开始的单行注释，这种注释可以单独占一行。

```c
/* 单行注释 */
/* 
 多行注释
 多行注释
 多行注释
 */
```

**/* */** 这种格式的注释可以单行或多行。

## 实例
```c
// 这是单行注释

/*
这是多行注释
它可以跨越多行
*/

int main() {
    // 打印一条消息
    printf("Hello, World!\n");
    return 0;
}
```
您不能在注释内嵌套注释，注释也不能出现在字符串或字符值中。

## 标识符

标识符是程序中变量、函数、数组等的名字。标识符由字母（大写或小写）、数字和下划线组成，但第一个字符必须是字母或下划线，不能是数字。

一个标识符以字母 A-Z 或 a-z 或下划线 _ 开始，后跟零个或多个字母、下划线和数字（0-9）。

C 标识符内不允许出现标点字符，比如 @、$ 和 %。C 是**区分大小写**的编程语言。因此，在 C 中，*Manpower* 和 *manpower* 是两个不同的标识符。下面列出几个有效的标识符：

```c
mohd       zara    abc   move_name  a_123
myname50   _temp   j     a23b9      retVal
```

## 常量

常量是固定值，在程序执行期间不会改变。

常量可以是整型常量、浮点型常量、字符常量、枚举常量等。

```c
constint MAX =100;// 整型常量
constfloat PI =3.14;// 浮点型常量
constchar NEWLINE ='\n';// 字符常量
```

## 字符串字面量

字符串字面量是由双引号括起来的字符序列。

字符串末尾会自动添加一个空字符 **\0**。

```c
char greeting[]="Hello, World!";
```

## 运算符（Operators）

运算符用于执行各种操作，如算术运算、逻辑运算、比较运算等。

C 语言中的运算符种类繁多，常见的包括：

* **算术运算符** ：`+`, `-`, `*`, `/`, `%`
* **关系运算符** ：`==`, `!=`, `>`, `<`, `>=`, `<=`
* **逻辑运算符** ：`&&`, `||`, `!`
* **位运算符** ：`&`, `|`, `^`, `~`, `<<`, `>>`
* **赋值运算符** ：`=`, `+=`, `-=`, `*=`, `/=`, `%=`
* **其他运算符** ：`sizeof`, `?:`, `&`, `*`, `->`, `.`

```c
int a =5, b =10;
int sum = a + b;// 使用算术运算符 +
int isEqual =(a == b);// 使用关系运算符 ==
```

## 关键字

下表列出了 C 中的保留字。这些保留字不能作为常量名、变量名或其他标识符名称。

| 关键字   | 说明                                                          |
| -------- | ------------------------------------------------------------- |
| auto     | 声明自动变量                                                  |
| break    | 跳出当前循环                                                  |
| case     | 开关语句分支                                                  |
| char     | 声明字符型变量或函数返回值类型                                |
| const    | 定义常量，如果一个变量被 const 修饰，那么它的值就不能再被改变 |
| continue | 结束当前循环，开始下一轮循环                                  |
| default  | 开关语句中的"其它"分支                                        |
| do       | 循环语句的循环体                                              |
| double   | 声明双精度浮点型变量或函数返回值类型                          |
| else     | 条件语句否定分支（与 if 连用）                                |
| enum     | 声明枚举类型                                                  |
| extern   | 声明变量或函数是在其它文件或本文件的其他位置定义              |
| float    | 声明浮点型变量或函数返回值类型                                |
| for      | 一种循环语句                                                  |
| goto     | 无条件跳转语句                                                |
| if       | 条件语句                                                      |
| int      | 声明整型变量或函数                                            |
| long     | 声明长整型变量或函数返回值类型                                |
| register | 声明寄存器变量                                                |
| return   | 子程序返回语句（可以带参数，也可不带参数）                    |
| short    | 声明短整型变量或函数                                          |
| signed   | 声明有符号类型变量或函数                                      |
| sizeof   | 计算数据类型或变量长度（即所占字节数）                        |
| static   | 声明静态变量                                                  |
| struct   | 声明结构体类型                                                |
| switch   | 用于开关语句                                                  |
| typedef  | 用以给数据类型取别名                                          |
| unsigned | 声明无符号类型变量或函数                                      |
| union    | 声明共用体类型                                                |
| void     | 声明函数无返回值或无参数，声明无类型指针                      |
| volatile | 说明变量在程序执行中可被隐含地改变                            |
| while    | 循环语句的循环条件                                            |

### C99 新增关键字

| _Bool | _Complex | _Imaginary | inline | restrict |
| ----- | -------- | ---------- | ------ | -------- |

### C11 新增关键字

| _Alignas       | _Alignof      | _Atomic | _Generic | _Noreturn |
| -------------- | ------------- | ------- | -------- | --------- |
| _Static_assert | _Thread_local |         |          |           |

## C 中的空格

只包含空格的行，被称为空白行，可能带有注释，C 编译器会完全忽略它。

在 C 中，空格用于描述空白符、制表符、换行符和注释。空格分隔语句的各个部分，让编译器能识别语句中的某个元素（比如 int）在哪里结束，下一个元素在哪里开始。因此，在下面的语句中：

```c
int age;
```

在这里，int 和 age 之间必须至少有一个空格字符（通常是一个空白符），这样编译器才能够区分它们。另一方面，在下面的语句中：

```c
fruit = apples + oranges;// 获取水果的总数
```

fruit 和 =，或者 = 和 apples 之间的空格字符不是必需的，但是为了增强可读性，您可以根据需要适当增加一些空格。
