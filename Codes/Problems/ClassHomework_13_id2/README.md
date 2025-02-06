# 移动链表中的元素
### `(对应nuaaoj课内实验13-id2)`
## 描述

在一个长度为 $n$ 的链表中(初始的时候为 $1$ -> $2$ -> $3$ -> $4$ ->...-> $n$ )，链表的编号即为它初始时候的位置，指定节点的编号，让其在链表中移动，输出经过 $m$ 次移动后的链表情况。
```c
typedef struct LinkNode{
  int num;
  struct LinkNode* next;
} Node;
```

## 输入

第一行输入一个正整数 $n(n>0)$ ，表示链表的长度。

第二行输入一个正整数 $m(m>0)$ ，表示移动链表中节点的次数。

接下来$m$行，每行输入两个整数 $p$ 和 $q$（ $q$ 可为任意整数负数，$0$ ，正数 ），分别表示 $num$ 为 $p$ 的节点在链表中移动 $q$ 步。 $q$ 为负数表示向前移动。

注意：移动的距离如果超出链表长度，则放在两端即成为头节点或者成为尾结点。


## 输出

输出 $n$ 个整数，即移动操作之后的链表节点情况，用空格隔开。


## 输入样例 1 
```
8
2
1 3
2 4
```
## 输出样例 1
```
3 4 1 5 2 6 7 8
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
typedef struct LinkNode
{
    int num;
    struct LinkNode *next;
} LinkNode;
typedef struct
{
    LinkNode *node;
} LinkHead;
typedef struct
{
    LinkNode *last;
    LinkNode *current;
} NodeResult;
LinkHead *create(int n)
{
    LinkHead *head = malloc(sizeof(LinkHead));
    LinkNode *current;
    for (size_t i = 0; i < n; i++)
    {
        if (i == 0)
        {
            current = malloc(sizeof(LinkNode));
            head->node = current;
        }
        else
        {
            current->next = malloc(sizeof(LinkNode));
            current = current->next;
        }
        current->num = i + 1;
    }
    return head;
}
NodeResult getElement(int index, LinkHead *head, int n)
{
    LinkNode *last = NULL;
    LinkNode *current = head->node;
    for (size_t i = 0; i < min(index + 1, n); i++)
    {
        last = current;
        current = current->next;
    }
    return (NodeResult){last, current};
}
void move(int num, int moveStep, LinkHead *head, int n)
{
    int index;
    LinkNode *last = NULL;
    LinkNode *target = head->node;
    for (size_t i = 0; i < n; i++)
    {
        if (target->num == num)
        {
            index = i;
            break;
        }
        else
        {
            last = target;
            target = target->next;
        }
    }
    NodeResult result = getElement(min(max(index + moveStep, 0), n - 1), head, n);
    if (result.last == NULL)
    {
        head->node = target;
    }
    else
    {
        result.last->next = target;
    }
    if (target->next != NULL)
    {
        if (last == NULL)
        {
            head->node = target->next;
        }
        else
        {
            last->next = target->next;
        }
    }
    target->next = result.current;
}
int main()
{
    int m, n;
    scanf("%d", &n);
    LinkHead *head = create(n);
    scanf("%d", &m);
    for (size_t i = 0; i < m; i++)
    {
        int p, q;
        scanf("%d %d", &p, &q);
        move(p, q, head, n);
    }
    LinkNode *current = head->node;
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", current->num);
        current = current->next;
    }
}
```
</details>