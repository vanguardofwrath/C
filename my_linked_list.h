#ifndef MY_LINKED_LIST
#define MY_LINKED_LIST

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode* next;
} ListNode;

void print_linked_list(ListNode* head) 
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

void push_linked_list(ListNode** head, int value) 
{
    if (!head) 
    {
        return;
    }

    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
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

    ListNode *temp = *head;
    while (temp->next)
    {
        temp = temp->next;
    }

    temp->next = node;
}

int pop_linked_list(ListNode** head) 
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

    ListNode *temp = *head;
    while (temp->next->next != NULL)
    {
        temp = temp->next;
    }

    int value = temp->next->value;
    free(temp->next);
    temp->next = NULL;
    return value;
}

int peek_linked_list(ListNode *head) {
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

void push_front_linked_list(ListNode **head, int value) {
    if (!head)
    {
        return;
    }

    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (!node) 
    {
        return;
    }
    
    node->value = value;
    node->next = *head;
    *head = node;
}

void pop_front_linked_list(ListNode **head, int value) {
    if (!head || !(*head))
    {
        return;
    }

    ListNode *temp = *head;
    *head = temp->next;
    free(temp);
}

int is_linked_list_empty(ListNode *head) {
    return !head;
}

#endif