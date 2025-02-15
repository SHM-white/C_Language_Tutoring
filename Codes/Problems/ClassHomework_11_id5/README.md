# 删除单词（指向二维数组的指针）

## 描述

编写程序实现：现有一篇文章，编程将文章中的指定单词 `the` 删除，并将删除单词后的文字输出。

## 要求：

1. 定义一个二维数组存放这篇文章。
2. 采用指向二维数组的指针。

## 输入

输入：输入文章，文章由多个段落组成，段落以 `.` 为结束标记，文章以 `#` 作为结束标记

## 输出

输出：删除指定单词的一段文字，输出最后一段之后无需输出换行符。

## 输入样例 1

```
I , rather than you , should do the work.
Because only I have the ability.
these are mine.
you are right the.#
```

## 输出样例 1

```
I , rather than you , should do  work.
Because only I have  ability.
these are mine.
you are right .
```
<details>
<summary>参考答案（自己写的）</summary>

```c
#ifdef __cplusplus
#include <iostream>
#include <cstring>
#include <vector>
#else
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#endif // __cplusplus

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
char toLower(char in)
{
    if (in >= 'A' && in <= 'Z')
    {
        return 'a' + (in - 'A');
    }
    return in;
}

int main()
{
    char text[102400];
    char c;
    int index = 0;
    while ((c = getchar()) != '#')
    {
        text[index] = c;
        index++;
    }
    int length = index;
    index = 0;
    while (index < length)
    {
        if (index <= length - 3)
        {

            if (
                (index == 0 ? true : (text[index - 1] == ' ')) && toLower(text[index]) == 't' && toLower(text[index + 1]) == 'h' && toLower(text[index + 2]) == 'e' && ((index == length - 3) ? (true) : (!(text[index + 3] >= 'a' && text[index + 3] <= 'z') && !(text[index + 3] >= 'A' && text[index + 3] <= 'Z'))))
            {
                index += 3;
                continue;
            }
        }
        putchar(text[index]);
        index++;
    }
}
```
</details>