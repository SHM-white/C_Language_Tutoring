# 口算练习题

## 题目描述

王老师正在教简单算术运算。细心的王老师收集了 $i$ 道学生经常做错的口算题，并且想整理编写成一份练习。 编排这些题目是一件繁琐的事情，为此他想用计算机程序来提高工作效率。王老师希望尽量减少输入的工作量，比如 $\texttt{5+8}$ 的算式最好只要输入 $\texttt 5$ 和 $\texttt 8$，输出的结果要尽量详细以方便后期排版的使用，比如对于上述输入进行处理后输出 $\texttt{5+8=13}$ 以及该算式的总长度 $6$。王老师把这个光荣的任务交给你，请你帮他编程实现以上功能。

## 输入格式

第一行一个整数 $i$。

接着的 $i$ 行为需要输入的算式，每行可能有三个数据或两个数据。

若该行为三个数据则第一个数据表示运算类型，$\texttt a$ 表示加法运算，$\texttt b$ 表示减法运算，$\texttt c$ 表示乘法运算，接着的两个数据表示参加运算的运算数。

若该行为两个数据，则表示本题的运算类型与上一题的运算类型相同，而这两个数据为运算数。

## 输出格式

输出 $2\times i$ 行。对于每个输入的算式，输出完整的运算式及结果，第二行输出该运算式的总长度。

## 样例 #1

### 样例输入 #1

```
4
a 64 46
275 125
c 11 99
b 46 64
```

### 样例输出 #1

```
64+46=110
9
275+125=400
11
11*99=1089
10
46-64=-18
9
```

## 提示

### 【数据规模与约定】

对于 $50\%$ 的数据，输入的算式都有三个数据，第一个算式一定有三个数据。

对于所有数据，${0< i \leq 50}$ ，运算数为非负整数且小于 $10000$。

[参考题解](https://www.luogu.com.cn/problem/solution/P1957)
<details>
<summary>参考答案（自己写的）</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define BUFFER_SIZE 1024
typedef enum
{
    Add,
    Subtract,
    Multiplying
} Operators;
void reverse(char *buffer, int len)
{
    for (int i = 0; i < len / 2; i++)
    {
        char temp = buffer[i];
        buffer[i] = buffer[len - i - 1];
        buffer[len - i - 1] = temp;
    }
}
void itoa1(int num, char *buffer, size_t bufferSize){
    if (num == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    int i = 0;
    int sign = (num < 0)? -1 : 1;
    num *= sign;
    while (num > 0)
    {
        buffer[i++] = num % 10 + '0';
        num /= 10;
    }
    if (sign < 0)
    {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    reverse(buffer, i);
}

int calculate(int num1, int num2, Operators op){
    switch (op)
    {
    case Add:
        return num1 + num2;
    case Subtract:
        return num1 - num2;
    case Multiplying:
        return num1 * num2;
    default:
        return 0;
    }
}
int main(){
    int n;
    scanf("%d\n", &n);
    char buf[BUFFER_SIZE];
    Operators currentOperator;
    char operatorSymbol[] = "+";
    for (size_t i = 0; i < n; i++)
    {
        fgets(buf, BUFFER_SIZE, stdin);
        char operator;
        sscanf(buf, "%c", &operator);
        bool hasOperator = true;
        int num1, num2;
        switch (operator)
        {
        case 'a':
            currentOperator = Add;
            operatorSymbol[0] = '+';
            break;
        case 'b':
            currentOperator = Subtract;
            operatorSymbol[0] = '-';
            break;
        case 'c':
            currentOperator = Multiplying;
            operatorSymbol[0] = '*';
            break;
        default:
            hasOperator = false;
            break;
        }
        hasOperator ? sscanf(buf, "%c %d %d", &operator, &num1, &num2) : sscanf(buf, "%d %d", &num1, &num2);
        int result = calculate(num1, num2, currentOperator);
        char snum1[BUFFER_SIZE], snum2[BUFFER_SIZE], sresult[BUFFER_SIZE];
        itoa1(num1, snum1, BUFFER_SIZE);
        itoa1(num2, snum2, BUFFER_SIZE);
        itoa1(result, sresult, BUFFER_SIZE);
        char final[BUFFER_SIZE] = "";
        strcat(final, snum1);
        strcat(final, operatorSymbol);
        strcat(final, snum2);
        final[strlen(final) + 1] = '\0';
        final[strlen(final)] = '=';
        strcat(final, sresult);
        puts(final);
        printf("%d\n", strlen(final));
    }
}
```
</detail>