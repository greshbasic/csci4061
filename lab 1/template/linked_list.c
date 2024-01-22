#include "linked_list.h"

// Head pointer for the linked list
Node *head = NULL;

Node *createNode(int value){
    Node *node =  (Node *)malloc(sizeof(Node));
    node->val = value;
    node->next = NULL;
    return node;
}

void insertLL(int value){
    // Cases to handle:
        // Empty linked list
        if(!head){
            head = createNode(value);
        }
        // value < head->val
        // value > last node in linked list
        // insert value within linked list
}

void freeLL(){
    Node *nextNode = NULL;
    while(head){
        nextNode = head -> next;
        free(head);
        head = nextNode;
    }
    head = NULL;
}

void displayLL(){
    Node *trav = head;
    while(trav){
        printf("%d ", trav->val);
        trav = trav->next;
    }
    printf("\n");
}