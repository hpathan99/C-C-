/*Linked List implementation
*/
#include<stdio.h>
#include<stdlib.h>

//establishing node parameters
struct Node{
    int data;
    struct Node *next;

};

int main(){
    int i, n, item;
    struct Node *p, *q, *head;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the value of the head node: ");
    scanf("%d", &item);

    q =(struct Node*)malloc(sizeof(struct Node));
    q->data = item;
    q->next = NULL;

    head = q;
    p = head;

    for(i = 1; i<n; i++){
        printf("Enter the value of the next node: ");
        scanf("%d", &item);

        q =(struct Node*)malloc(sizeof(struct Node));
        q->data = item;
        q->next = NULL;

        p->next = q;//Link the nodes
        p = p->next;//jump to current node
        
    }

    printf("\n");
    p = head;
    while (p != NULL){
        printf("%d", p->data);
        p = p->next;
    }
    return (0);
}
