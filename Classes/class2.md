# Class 2

## 1. 补充前一节课内容

- 逻辑运算符的短路，以及按位运算符
- 函数的形参与实参
- `for`循环的其它写法
- 变量的命名规则
- enum类型的使用方法

### 1.1 逻辑运算符的短路及按位运算符

逻辑运算符的短路，是指当运算符的左边的表达式可以确定整个表达式的结果时，右边的表达式就不必计算了。

实例：

```c
#include <stdio.h>
int func(int return_value, int id){
    printf("id = %d, return_value = %d\n", id, return_value);
    return return_value;
}
int main(){
    int a = func(1, 1) || func(1, 2);
    // 输出结果：id = 1, return_value = 1
    // 由于第一个函数的返回值是1，因此整个表达式的结果为1，因此第二个函数就不必计算了。
    int b = func(0, 3) && func(1, 4);
    // 输出结果：id = 3, return_value = 0
    // 由于第一个函数的返回值是0，因此整个表达式的结果为0，因此第二个函数就不必计算了。
    int c = func(1, 5) && func(0, 6);
    // 输出结果：id = 5, return_value = 1
    //          id = 6, return_value = 0
    // 由于第一个函数的返回值是1，整个表达式的结果仍可能为0，因此第二个函数的返回值也会被计算。
    return 0;
}
```
按位运算符：

见cppreference[算术运算符](https://zh.cppreference.com/w/c/language/operator_arithmetic)

- `&`：按位与运算符，两个操作数相应位都为1时，结果才为1，否则为0。
- `|`：按位或运算符，两个操作数相应位有一个为1时，结果为1，否则为0。
- `^`：按位异或运算符，两个操作数相应位不同时，结果为1，否则为0。
- `~`：按位取反运算符，对操作数的每个二进制位取反，即0变1，1变0。
- `<<`：左移运算符，将操作数的各二进制位向左移动指定的位数。
- `>>`：右移运算符，将操作数的各二进制位向右移动指定的位数。

实例：
```c
#include <stdio.h>
#include <stdint.h>
 
int main(void)
{
    uint32_t a = 0x12345678;
    uint16_t mask = 0x00f0;
 
    printf("Promoted mask:\t%#010x\n"
           "Value:\t\t%#x\n"
           "Setting bits:\t%#x\n"
           "Clearing bits:\t%#x\n"
           "Selecting bits:\t%#010x\n"
           , mask
           , a
           , a | mask
           , a & ~mask
           , a & mask
    );
}
```
可能的输出：
```
Promoted mask:  0x000000f0
Value:          0x12345678
Setting bits:   0x123456f8
Clearing bits:  0x12345608
Selecting bits: 0x00000070
```
实例：
```c
#include <stdio.h>
enum {ONE=1, TWO=2};
int main(void)
{
    char c = 0x10;
    unsigned long long ulong_num = 0x123;
    printf("0x123 << 1  = %#llx\n"
           "0x123 << 63 = %#llx\n"   // 对无符号数，溢出截断高位
           "0x10  << 10 = %#x\n",    // char 被提升到 int
           ulong_num << 1, ulong_num << 63, c << 10);
    long long long_num = -1000;
    printf("-1000 >> 1 = %lld\n", long_num >> ONE);  // 实现定义
}
```
可能的输出：
```
0x123 << 1  = 0x246
0x123 << 63 = 0x8000000000000000
0x10  << 10 = 0x4000
-1000 >> 1 = -500
```

补充：[其它运算符](https://zh.cppreference.com/w/c/language/operator_other)

### 1.2 函数的形参与实参

函数的形参（parameter）是函数定义时定义的变量，函数的实参（argument）是调用函数时传入的实际值。

函数的声明格式：

```c
return_type function_name(parameter_list);
```

1. `return_type`：表示函数的返回值的数据类型。
2. `function_name`：表示函数的名称。
3. `parameter_list`：表示函数的形参列表，形参之间用逗号分隔。

   形参列表的每个元素的格式：

   ```c
   type parameter_name
   ```
1. `type`：表示变量的数据类型。
2. `parameter_name`：表示变量的名称。

函数的调用格式：

```c
function_name(argument1, argument2,..., argumentn);
```

1. `function_name`：表示函数的名称。
2. `argument1, argument2,..., argumentn`：表示函数调用时传入的实际值。

实例：

```c
#include <stdio.h>
void print_info(char *name, int age){
    printf("Name: %s, Age: %d\n", name, age);
}
int main(){
    print_info("Tom", 20);
    // 输出结果：Name: Tom, Age: 20
    return 0;
}
```

name和age是函数print_info的形参，"Tom"和20是函数print_info的实参。

### 1.3 `for`和`while`循环的其它写法

`for`循环的写法：

```c
for(initialization; condition; iteration){
    // loop body
}
```

1. `initialization`：表示循环的初始化语句，一般用来初始化循环的计数器。
2. `condition`：表示循环的条件表达式，循环的条件为真时，循环才继续，为假时，循环结束。
3. `iteration`：表示循环的迭代语句，一般用来更新循环的计数器。
4. `loop body`：表示循环的主体，循环执行的语句。

`initialization`,`condition`和`iteration`均可省略，例如：

```c
initialization;
for(;;){
    // loop body
    iteration;
}
```
`condition`默认为`true`，可在循环体内使用`break`和`continue`语句来控制循环。
### 1.4 变量的命名规则

变量的命名规则：

1. 变量名只能包含字母、数字和下划线。
2. 变量名的第一个字符不能是数字。
3. 变量名的长度不能超过31个字符。
4. 变量名的命名应能反映变量的用途。

变量命名风格：

1. 驼峰命名法：分为大驼峰命名法和小驼峰命名法。
   - 大驼峰命名法（帕斯卡命名法）：每个单词的首字母都大写，一般用于类名/结构体名，例如：`StudentList`，`EmployeeInfo`。
   - 小驼峰命名法：每个单词的首字母都小写，一般用于变量名，例如：`firstName`，`lastName`。
2. 匈牙利命名法：该命名规范，要求前缀字母用变量类型的缩写，其余部分用变量的英文或英文的缩写，单词第一个字母大写。
```
int iMyAge;        #  "i": int
char cMyName[10];  #  "c": char
float fManHeight;  #  "f": float
```
3. 下划线命名法：该命名规范，要求变量名中每个单词的首字母都小写，单词之间用下划线连接。
```
int my_age;
char my_name[10];
float man_height;
```

变量的生命周期越短，名称应越简洁，最典型的例子就是循环变量，例如：
```c
for(int i = 0; i < 10; i++){
    // do something
}
```
变量`i`的生命周期仅在循环体内，所以可以用`i`作为循环变量的名称。

### 1.5 enum类型的使用方法

enum类型是一种基本数据类型，用于定义一组整型常量。

enum类型定义格式：

```c
enum 枚举类型名{
    枚举元素1,
    枚举元素2,
    枚举元素3,
   ...
};
```

例：

```c
enum Color{
    RED,    // 0
    GREEN,  // 1
    BLUE    // 2
};
```
enum类型可以像普通整型常量一样使用，例如：

```c
Color color = RED;
// 或者
Color color = 0;// 等价于RED
```
enum也可以用在switch语句中，例如：

```c
switch(color){
    case RED:
        printf("The color is red.\n");
        break;
    case GREEN:
        printf("The color is green.\n");
        break;
    case BLUE:
        printf("The color is blue.\n");
        break;
    default:
        printf("Invalid color.\n");
        break;
}
```
相比直接使用整型常量，enum类型有以下优点：

1. 枚举类型可以使代码更易读，更易理解。
2. 枚举类型可以避免因数字值改变导致的错误。
3. 枚举类型可以使代码更加安全，因为枚举元素只能是预定义的常量。

## 2. 题目讲解

- [字符串处理函数](../Codes/Functions/String_Functions.md)
- [递归函数](../Codes/Functions/Recursion_Functions.md)
- [排序函数](../Codes/Functions/Sort_Functions.md)(上次讲过)
- [链表操作函数](../Codes/Functions/List_Functions.md)
- [文件的读写](https://zh.cppreference.com/w/c/io/fopen)，[实例](../Codes/Usage_Examples/File_Operations.c)