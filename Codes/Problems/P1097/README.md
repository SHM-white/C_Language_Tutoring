# [NOIP 2007 提高组] 统计数字

## 题目描述

某次科研调查时得到了 $n$ 个自然数，每个数均不超过 $1.5 \times 10^9$。已知不相同的数不超过 $10^4$ 个，现在需要统计这些自然数各自出现的次数，并按照自然数从小到大的顺序输出统计结果。

## 输入格式

共 $n+1$ 行。

第一行是整数 $n$，表示自然数的个数；

第 $2$ 至 $n+1$ 每行一个自然数。

## 输出格式

共 $m$ 行（$m$ 为 $n$ 个自然数中不相同数的个数），按照自然数从小到大的顺序输出。  

每行输出 $2$ 个整数，分别是自然数和该数出现的次数，其间用一个空格隔开。

## 样例 #1

### 样例输入 #1

```
8
2
4
2
4
5
100
2
100
```

### 样例输出 #1

```
2 3
4 2
5 1
100 2
```

## 提示

- $30\%$ 的数据满足：$1  \le  n  \le  1000$；
- $60\%$ 的数据满足：$1  \le  n  \le  50000$；
- $100\%$ 的数据满足：$1  \le  n  \le  200000$，每个数均不超过 $1.5 \times 10^9$。

NOIP 2007 提高第一题

[参考题解](https://www.luogu.com.cn/problem/solution/P1097)
<details>
<summary>参考答案（自己写的）</summary>

```c
#include <stdio.h>
#include <stdlib.h>
void sort(int *data, int size){
    for (size_t i = 1; i < size; i++)
    {
        for (size_t j = 0; j < size - i - 1; j++)
        {
            if(data[j] > data[j + 1]){
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}
int compare(const void *arg1, const void *arg2){
    int a = *(int *)arg1;
    int b = *(int *)arg2;
    if(a == b){
        return 0;
    }
    return a > b ? 1 : -1;
}
int main()
{
    int n;
    scanf("%d", &n);
    int *dataContent = calloc(n, sizeof(int));
    for (size_t i = 0; i < n; i++)
    {
        scanf("%d", dataContent + i);
    }
    qsort(dataContent, n, sizeof(int), compare);
    // sort(dataContent, n);
    int lastData = dataContent[0];
    int counter = 0;
    for (size_t i = 0; i < n; i++)
    {
        if(i == 0){
            printf("%d", lastData);
            counter = 1;
        }else if(lastData != dataContent[i]){
            printf(" %d\n", counter);
            counter = 1;
            printf("%d", dataContent[i]);
            lastData = dataContent[i];
        }
        else
        {
            counter++;
        }
        if (i == n - 1)
        {
            printf(" %d\n", counter);
        }
    }
    
}
```
</details>