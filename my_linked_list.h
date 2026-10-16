#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct MyListNode {
    int value;
    struct MyListNode* next;
} MyListNode;

void my_linked_list_push(MyListNode **head, int value);
int my_linked_list_pop(MyListNode **head);
int my_linked_list_peek(MyListNode *head);
void my_linked_list_push_front(MyListNode **head, int value);
void my_linked_list_pop_front(MyListNode **head, int value);
void my_linked_list_print(MyListNode *head);
void my_linked_list_empty(MyListNode **head);

// --------------------------------------------------------------------------------------

void my_linked_list_push(MyListNode** head, int value) 
{
    if (!head) 
    {
        return;
    }

    MyListNode *node = (MyListNode *)malloc(sizeof(MyListNode));
    if (!node)
    {
        return;
    }

    node->next = NULL;
    node->value = value;

    if (!(*head))
    {
        (*head) = node;
        return;
    }

    MyListNode *temp = *head;
    while (temp->next)
    {
        temp = temp->next;
    }

    temp->next = node;
}

int my_linked_list_pop(MyListNode** head) 
{
    if (!head || !(*head)) 
    {
        return -1;
    }

    if (!(*head)->next) 
    {
        int value = (*head)->value;
        free(*head);
        *head = NULL;
        return value;
    }

    MyListNode *temp = *head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    int value = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    return value;
}

int my_linked_list_peek(MyListNode *head) {
    if (!head)
    {
        return -1;
    }

    while (head->next)
    {
        head = head->next;
    }

    return head->value;
}

void my_linked_list_push_front(MyListNode **head, int value) {
    if (!head)
    {
        return;
    }

    MyListNode *node = (MyListNode *)malloc(sizeof(MyListNode));
    if (!node) 
    {
        return;
    }
    
    node->value = value;
    node->next = *head;
    *head = node;
}

void my_linked_list_pop_front(MyListNode **head, int value) {
    if (!head || !(*head))
    {
        return;
    }

    MyListNode *temp = *head;
    *head = temp->next;
    free(temp);
}

void my_linked_list_print(MyListNode* head) 
{
    if (!head) 
    {
        return;
    }

    while (head->next) {
        printf("%d, ", head->value);
        head = head->next;
    }

    printf("%d\n",head->value);
}

void my_linked_list_empty(MyListNode **head) {
    if (!head) {
        return;
    }
    
    while (*head) {
        MyListNode *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

#endif