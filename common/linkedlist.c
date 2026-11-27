#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "linkedlist.h"

void linked_list_push(ListNode **head, void *value)
{
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

    ListNode *current = *head;
    while (current->next)
    {
        current = current->next;
    }

    current->next = node;
}

void *linked_list_pop(ListNode **head)
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

    ListNode *current = *head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }

    void *to_return = current->next->value;
    free(current->next);
    current->next = NULL;
    return to_return;
}

void *linked_list_peek(ListNode *head)
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

void linked_list_push_front(ListNode **head, void *value)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    if (!node)
    {
        return;
    }

    node->value = value;
    node->next = *head;
    *head = node;
}

void *linked_list_pop_front(ListNode **head)
{
    if (!(*head))
    {
        return NULL;
    }

    ListNode *to_remove = *head;
    void *to_return = to_remove->value;
    *head = to_remove->next;
    free(to_remove);
    return to_return;
}

void *linked_list_peek_front(ListNode *head) {
    if (!head) {
        return NULL;
    }

    return head->value;
}

void linked_list_free(ListNode **head, void (*destroy_function)(void *value))
{
    while (*head)
    {
        ListNode *temp = *head;
        *head = (*head)->next;
        if (destroy_function && temp->value)
        {
            destroy_function(temp->value);
        }
        free(temp);
    }
}