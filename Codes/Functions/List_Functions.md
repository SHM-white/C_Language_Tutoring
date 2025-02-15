# 链表操作函数

## 0.链表定义：

### 单向链表：
```c
struct Node {
    int data;
    struct Node* next;
};
//声明方式：
struct Node* head = NULL; //头指针
```
```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;
//声明方式：
Node* head = NULL; //头指针
```
>后面的函数均以单向链表为例
### 双向链表：

```c
typedef struct Node {
    int data;
    struct Node* last;
    struct Node* next;
} Node;
//声明方式：
Node* head = NULL; //头指针
```
>使用方式可由单向链表的对应函数修改
## 1. 链表创建函数

```c
//Create a new node while inputting data in stdin
Node* createNode() {
    Node *head = NULL;
    Node *current = NULL;
    while(1){    
        int input;
        printf("Enter data: ");
        scanf("%d", &input);
        if(input == -1) break;
        if(head == NULL) {
            head = (Node*)malloc(sizeof(Node));
            current = head;
        } else {
            current->next = (Node*)malloc(sizeof(Node));
            current = current->next;
        }
        current->data = input;
        current->next = NULL;
    } //输入-1结束输入
    //环形链表处理
    //current->next = head;
    return head;
}
```
## 2. 链表打印函数

```c
//Print the linked list
void printList(Node* head) {
    Node* current = head;
    while(current!= NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
```

## 3. 链表插入函数

```c
//Insert a new node at the beginning of the linked list
void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}
```
```c
//Insert a new node at the target position of the linked list
void insertAtPosition(Node** head_ref, int new_data, int position) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    Node* current = *head_ref;
    Node* prev = NULL;
    int i = 1;
    while(current!= NULL && i < position) {
        prev = current;
        current = current->next;
        i++;
    }
    if(current == NULL) {
        printf("Position is out of range.\n");
        return;
    }
    new_node->next = current;
    if(prev == NULL) {
        *head_ref = new_node;
    } else {
        prev->next = new_node;
    }
}
```

## 4. 链表删除函数

```c
//Delete a node from the linked list
void deleteNode(Node** head_ref, int key) {
    Node* current = *head_ref;
    Node* prev = NULL;
    while(current!= NULL && current->data!= key) {
        prev = current;
        current = current->next;
    }
    if(current == NULL) return;
    if(prev == NULL) {
        *head_ref = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}
``` 
```c
//Delete the entire linked list
void deleteList(Node** head_ref) {
    Node* current = *head_ref;
    Node* next = NULL;
    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}
```
## 5. 链表合并函数

```c
//Merge two linked lists
Node* mergeLists(Node* a, Node* b) {
    Node* result = NULL;
    Node** tail = &result;
    while(a!= NULL && b!= NULL) {
        if(a->data < b->data) {
            *tail = a;
            a = a->next;
        } else {
            *tail = b;
            b = b->next;
        }
        tail = &((*tail)->next);
    }
    if(a!= NULL) {
        *tail = a;
    } else {
        *tail = b;
    }
    return result;
}
```