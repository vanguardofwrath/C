#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct MyListNode
{
    void *value;
    struct MyListNode *next;
} MyListNode;

void my_linked_list_push(MyListNode **head, void *value);
void *my_linked_list_pop(MyListNode **head);
void my_linked_list_push_front(MyListNode **head, void *value);
void *my_linked_list_pop_front(MyListNode **head);
void *my_linked_list_peek(MyListNode *head);
void my_linked_list_free(MyListNode **head, void (*destroy_function)(void *value));

void my_linked_list_push(MyListNode **head, void *value)
{
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

    MyListNode *current = *head;
    while (current->next)
    {
        current = current->next;
    }

    current->next = node;
}

void *my_linked_list_pop(MyListNode **head)
{
    if (!(*head))
    {
        return NULL;
    }

    if (!(*head)->next)
    {
        void *value = (*head)->value;
        free(*head);
        *head = NULL;
        return value;
    }

    MyListNode *current = *head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    void *to_return = current->next->value;
    free(current->next);
    current->next = NULL;
    return to_return;
}

void *my_linked_list_peek(MyListNode *head)
{
    if (!head)
    {
        return NULL;
    }

    while (head->next)
    {
        head = head->next;
    }

    return head->value;
}

void my_linked_list_push_front(MyListNode **head, void *value)
{
    MyListNode *node = (MyListNode *)malloc(sizeof(MyListNode));
    if (!node)
    {
        return;
    }

    node->value = value;
    node->next = *head;
    *head = node;
}

void *my_linked_list_pop_front(MyListNode **head)
{
    if (!(*head)) {
        return NULL;
    }

    MyListNode *to_remove = *head;
    void *to_return = to_remove->value;
    *head = to_remove->next;
    free(to_remove);
    return to_return;
}

void my_linked_list_free(MyListNode **head, void (*destroy_function)(void *value))
{
    while (*head)
    {
        MyListNode *temp = *head;
        *head = (*head)->next;
        destroy_function(temp->value);
        free(temp);
    }
}

#endif