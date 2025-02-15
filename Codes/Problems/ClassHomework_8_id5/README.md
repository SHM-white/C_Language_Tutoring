# [高难题]和为T

## 描述

**[此题为高难度题, 请学有余力时再完成]**

从一个大小为$n$的整数集中选取一些元素，使得它们的和等于给定的值$T$。每个元素限选一次，不能一个都不选。

## 输入

第一行一个正整数$n$，表示整数集内元素的个数。

第二行$n$个整数，用空格隔开。

第三行一个整数$T$，表示要达到的和。

输入样例:
```
5
-7 -3 -2 5 9
0
```
## 输出

输出有若干行，每行输出一组解，即所选取的数字，按照输入中的顺序排列。

若有多组解，优先输出不包含第$n$个整数的；若都包含或都不包含，优先输出不包含第${n-1}$个整数的，依次类推。

最后一行输出总方案数。

输出样例:
```
-3 -2 5
-7 -2 9
2
```


## 提示
```
HINT:时间限制：1.0s 内存限制：256.0MB
```
${1<=n<=22}$

${T<=maxlongint}$

集合中任意元素的和都不超过`long`的范围

## 来源
蓝桥杯练习系统 ID: 290 原题链接: http://lx.lanqiao.cn/problem.page?gpid=T290


[论坛答案](https://blog.csdn.net/qq_45281807/article/details/104427092)(标准递归法)
<details>
<summary>参考答案（自己写的）</summary>

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int n;
    long long *nums;
    long long target;
    scanf("%d", &n);
    nums = calloc(n, sizeof(long long));
    for (size_t i = 0; i < n; i++)
    {
        scanf("%lld", &nums[i]);
    }
    scanf("%lld", &target);
    register unsigned long long index = 0b01;
    unsigned int count = 0;
    while (index < 0b01 << n)
    {
        long long sum = 0;
        for (size_t i = 0; i < n; i++)
        {
            if (index & 0b01 << i){
                sum += nums[i];
            }
        }
        if (sum == target)
        {
            for (size_t i = 0; i < n; i++)
            {
                if(index & 0b01 << i){
                    printf("%lld ", nums[i]);
                }
            }
            printf("\n");
            count++;
        }
        index++;
    }
    printf("%u", count);
}
```
</details>