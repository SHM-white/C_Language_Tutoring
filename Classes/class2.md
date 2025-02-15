# Class 2

## 1. 补充前一节课内容

- 逻辑运算符的短路，以及对应的按位运算符
- 函数的形参与实参
- `for`和`while`循环的其它写法
- 变量的命名规则

### 1.1 逻辑运算符的短路

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
    return 0;
}
```