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
            return;
        }

        // value < head->val
        if(value < head->val){
            Node *new = createNode(value);
            new->next = head;
            head = new;
            return;
        }

        // value > last node in linked list
        Node *currNode = head;
        while (currNode->next){
            currNode = currNode->next;
        }
        if (currNode->val < value){
            currNode->next = createNode(value);
            return;
        }

        // insert value within linked list
        currNode = head->next;
        Node *prevNode = head;

        while (currNode){
            if (value <= currNode->val){
                Node *new = createNode(value);
                new->next = currNode;
                prevNode->next = new;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
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