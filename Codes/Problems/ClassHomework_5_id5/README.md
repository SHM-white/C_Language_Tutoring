# 基础练习 回形取数

## 描述

回形取数就是沿矩阵的边取数，若当前方向上无数可取或已经取过，则左转90度。一开始位于矩阵左上角，方向向下。

## 输入

输入描述:

输入第一行是两个不超过200的正整数m, n，表示矩阵的行和列。接下来m行每行n个整数，表示这个矩阵。

输入样例:

```
3 3
1 2 3
4 5 6
7 8 9
```


## 输出

输出描述:

输出只有一行，共mn个数，为输入矩阵回形取数得到的结果。数之间用一个空格分隔，行末不要有多余的空格。

输出样例:

`1 4 7 8 9 6 3 2 5`

## 输入样例 1 

```
参考上文 
```

## 输出样例 1

```
参考上文
```

## 提示
```
HINT:时间限制：1.0s 内存限制：512.0MB
```
## 来源

蓝桥杯练习系统 ID: 66 原题链接: http://lx.lanqiao.cn/problem.page?gpid=T66

<details>
<summary>参考答案（自己写的）</summary>

```c
#ifdef __cplusplus
#include <iostream>
#include <vector>
#else
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#endif // __cplusplus

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
typedef enum
{
    Down,
    Up,
    Left,
    Right
} Direction;
int main()
{
    int **map;
    int **memo;
    int m, n;
    scanf("%d %d", &m, &n);
    map = (int **)calloc(m, sizeof(int *));
    memo = (int **)calloc(m, sizeof(int *));
    for (size_t i = 0; i < m; i++)
    {
        map[i] = (int *)calloc(n, sizeof(int));
        memo[i] = (int *)calloc(n, sizeof(int));
        for (size_t j = 0; j < n; j++)
        {
            scanf("%d", &map[i][j]);
            memo[i][j] = 0;
        }
    }
    {
        int i = 0, j = 0;
        Direction currentDirection = Down;
        int failCount = 0;
        while (1)
        {
            if(memo[i][j] == 0)
            {
                printf("%d ", map[i][j]);
                failCount = 0;
            }
            else
            {
                failCount++;
            }
            if(failCount > 1){
                break;
            }
            switch (currentDirection)
            {
            case Down:
                memo[i][j] = 1;
                if (i + 1 < m && memo[i + 1][j] == 0)
                {
                    i++;
                }
                else
                {
                    currentDirection = Right;
                }
                break;
            case Up:
                memo[i][j] = 1;
                if (i - 1 >= 0 && memo[i - 1][j] == 0)
                {
                    i--;
                }
                else
                {
                    currentDirection = Left;
                }
                break;
            case Left:
                memo[i][j] = 1;
                if (j - 1 >= 0 && memo[i][j - 1] == 0)
                {
                    j--;
                }
                else
                {
                    currentDirection = Down;
                }
                break;
            case Right:
                memo[i][j] = 1;
                if (j + 1 < n && memo[i][j + 1] == 0)
                {
                    j++;
                }
                else
                {
                    currentDirection = Up;
                }
                break;
            default:
                break;
            }
        }
    }
}
```
</details>