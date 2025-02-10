# 单向链表

## 题目描述

实现一个数据结构，维护一张表（最初只有一个元素 $1$）。需要支持下面的操作，其中 $x$ 和 $y$ 都是 $1$ 到 $10^6$ 范围内的正整数，且保证任何时间表中所有数字均不相同，操作数量不多于 $10^5$：

- `1 x y` ：将元素 $y$ 插入到 $x$ 后面；
- `2 x` ：询问 $x$ 后面的元素是什么。如果 $x$ 是最后一个元素，则输出 $0$；
- `3 x`：从表中删除元素 $x$ **后面的那个元素**，不改变其他元素的先后顺序。

## 输入格式

第一行一个整数 $q$ 表示操作次数。

接下来 $q$ 行，每行表示一次操作，操作具体见题目描述。

## 输出格式

对于每个操作 2，输出一个数字，用换行隔开。

## 样例 #1

### 样例输入 #1

```
6
1 1 99
1 99 50
1 99 75
2 99
3 75
2 1
```

### 样例输出 #1

```
75
99
```

[参考题解](https://www.luogu.com.cn/problem/solution/B3631)
<details>
<summary>参考答案（自己写的）</summary>

全AC解法：
```c
#include <stdio.h>
#include <stdlib.h>
int nums[1000] = {0};
inline void insert(int target, int value){
    nums[value] = nums[target];
    nums[target] = value;
    nums[0] = 0;
}
inline int whatIsTheNextValue(int target){
    return nums[target];
}
inline void deleteNext(int target){
    int tmp = nums[target];
    nums[target] = nums[tmp];
    nums[tmp] = 0;
}
int main(){

    int n;
    scanf("%d\n", &n);
    char **commands = (char **)calloc(n, sizeof(char *));
    for (size_t i = 0; i < n; i++)
    {
        commands[i] = (char *)calloc(10, sizeof(char));
        gets(commands[i]);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        int opt, target, value;
        sscanf(commands[i], "%d %d %d", &opt, &target, &value);
        switch (opt)
        {
        case 1:
            insert(target, value);
            break;
        case 2:
            printf("%d\n", whatIsTheNextValue(target));
            break;
        case 3:
            deleteNext(target);
            break;
        default:
            break;
        }
    }
}
```
链表解法：
```c
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int num;
    struct Node *next;
} Node;
Node *end;
inline Node *findItem(Node *head, int target){
    static Node *lastResult;
    if(lastResult != NULL && lastResult->num == target){
        return lastResult;
    }
    if(end->num == target){
        lastResult = end;
        return end;
    }
    Node *current = head;
    while (current->num != target)
    {
        // if(current == NULL){
        //     return NULL;
        // }
        current = current->next;
    }
    lastResult = current;
    return current;
}
inline void insert(Node *head, int target, int value){
    Node *current = findItem(head, target);
    //if(current ==  NULL){ return; }
    Node *p = (Node *)malloc(sizeof(Node));
    if(current == end){
        end = p;
    }
    p->num = value;
    p->next = current->next;
    current->next = p;
}
inline int whatIsTheNextValue(Node *head, int target){
    if(end->num == target){
        return 0;
    }
    Node *current = findItem(head, target);
    //if(current ==  NULL){ return 0; }
    return current->next->num;
}
inline void deleteNext(Node *head, int target){
    Node *current = findItem(head, target);
    //if(current ==  NULL){ return; }
    if(current->next == NULL){
        return;
    }
    if(current->next == end){
        end = current;
    }
    Node *tmp = current->next;
    current->next = tmp->next;
    free(tmp);
}
int main(){
    Node *list = (Node *)malloc(sizeof(Node));
    end = list;
    list->num = 1;
    list->next = NULL;
    int n;
    scanf("%d\n", &n);
    char **commands = (char **)calloc(n, sizeof(char *));
    for (size_t i = 0; i < n; i++)
    {
        commands[i] = (char *)calloc(10, sizeof(char));
        gets(commands[i]);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        int opt, target, value;
        sscanf(commands[i], "%d %d %d", &opt, &target, &value);
        switch (opt)
        {
        case 1:
            insert(list, target, value);
            break;
        case 2:
            printf("%d\n", whatIsTheNextValue(list, target));
            break;
        case 3:
            deleteNext(list, target);
            break;
        default:
            break;
        }
    }
}
```
</details>