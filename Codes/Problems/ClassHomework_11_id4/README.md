# 字符大小写处理（指向二维数组的指针）
## 描述

定义一个二维数组，用于存放多行字符串。编写程序实现：在主函数中输入多个句子，并定义一个函数`ConvertSentence`，对存放在二维数组中的多行句子进行处理：使得各句子首字母大写、句子中其它字母均为小写。在主函数中调用`ConvertSentence`函数，输出经过处理的句子。
## 要求：

1. 采用指向二维数组的指针实现；
2. `ConvertSentence`函数原型为：`void convert_Sentence(char (*pStr) [200])`

## 输入：

1. 句子数（字符串数）$N$
2. $N$行句子

## 输出：
经过大小写处理后的句子

## 输入样例 1 
```
2
HEllo, world!
travelling light.
```
## 输出样例 1
```
Hello, world!
Travelling light.
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
int n;
char toUper(char in){
    if(in >= 'a' && in <= 'z'){
        return 'A' + (in - 'a');
    }
    return in;
}
char toLower(char in){
    if(in >= 'A' && in <= 'Z'){
        return 'a' + (in - 'A');
    }
    return in;
}
void convert_Sentence2(char *pStr){
    int index = 0;
    int sentence_begin = 1;
    while (pStr[index] != '\0')
    {
        while(pStr[index] == ' '){
            index++;
        }
        if(sentence_begin == 1){
            pStr[index] = toUper(pStr[index]);
            sentence_begin = 0;
        }
        else{
            pStr[index] = toLower(pStr[index]);
        }
        if(pStr[index] == '.'){
            sentence_begin = 1;
        }
        if(pStr[index] == '!'){
            sentence_begin = 1;
        }
        if(pStr[index] == '?'){
            sentence_begin = 1;
        }
        index++;
    }
} 

void convert_Sentence(char (*pStr)[200]){
    for (size_t i = 0; i < n; i++)
    {
        convert_Sentence2(pStr[i]);
    }   
} 
int main()
{
    char texts[100][200];
    scanf("%d\n", &n);
    
    for (size_t i = 0; i < n; i++)
    {
        gets(texts[i]);
        texts[i][strcspn(texts[i], "\n")] = 0;
    }
    convert_Sentence(texts);
    for (size_t i = 0; i < n; i++)
    {
        printf("%s\n", texts[i]);
    }

}
```
</details>