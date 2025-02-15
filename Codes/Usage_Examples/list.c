#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int num;
    struct Node *next;
} Node;
Node *findItem(Node *head, int target){
    Node *current = head;
    while (current->num != target)
    {
        if(current == NULL){
            return NULL;
        }
        current = current->next;
    }
    return current;
}
void insert(Node *head, int target, int value){
    Node *current = findItem(head, target);
    if(current ==  NULL){ return; }
    Node *p = (Node *)malloc(sizeof(Node));
    p->num = value;
    p->next = current->next;
    current->next = p;
}
int whatIsTheNextValue(Node *head, int target){
    Node *current = findItem(head, target);
    if(current ==  NULL){ return 0; }
    if(current->next == NULL){
        return 0;
    }
    return current->next->num;
}
void deleteNext(Node *head, int target){
    Node *current = findItem(head, target);
    if(current ==  NULL){ return; }
    if(current->next == NULL){
        return;
    }
    Node *tmp = current->next;
    current->next = tmp->next;
    free(tmp);
}
int main(){
    Node *list = (Node *)malloc(sizeof(Node));
    list->num = 1;
    list->next = NULL;
    int n;
    scanf("%d", &n);
    for (size_t i = 0; i < n; i++)
    {
        int opt, target, value;
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            scanf("%d %d", &target, &value);
            insert(list, target, value);
            break;
        case 2:
            scanf("%d", &target);
            printf("%d\n", whatIsTheNextValue(list, target));
            break;
        case 3:
            scanf("%d", &target);
            deleteNext(list, target);
            break;
        default:
            break;
        }
    }
}