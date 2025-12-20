#include <stdio.h>
#include <stdlib.h>

// 链表节点定义
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建链表（输入-1结束）
Node* createNode() {
    Node *head = NULL;
    Node *current = NULL;
    while(1){    
        int input;
        printf("Enter data (-1 to end): ");
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
    }
    return head;
}

// 打印链表
void printList(Node* head) {
    Node* current = head;
    printf("List: ");
    while(current!= NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 头插法
void insertAtBeginning(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// 指定位置插入
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
    if(current == NULL && i < position) {
        printf("Position is out of range.\n");
        free(new_node);
        return;
    }
    new_node->next = current;
    if(prev == NULL) {
        *head_ref = new_node;
    } else {
        prev->next = new_node;
    }
}

// 删除指定值节点
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

// 删除整个链表
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

// 合并两个有序链表
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

int main() {
    printf("创建链表A：\n");
    Node* headA = createNode();
    printList(headA);

    printf("\n在链表A头部插入99：\n");
    insertAtBeginning(&headA, 99);
    printList(headA);

    printf("\n在链表A第3个位置插入77：\n");
    insertAtPosition(&headA, 77, 3);
    printList(headA);

    printf("\n删除链表A中的99：\n");
    deleteNode(&headA, 99);
    printList(headA);

    printf("\n创建链表B：\n");
    Node* headB = createNode();
    printList(headB);

    printf("\n合并链表A和B（假设有序）：\n");
    Node* merged = mergeLists(headA, headB);
    printList(merged);

    printf("\n删除合并后的链表：\n");
    deleteList(&merged);
    printList(merged);

    return 0;
}
