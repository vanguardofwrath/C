#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ListNode
{
    void *value;
    struct ListNode *next;
} ListNode;

void linked_list_push(ListNode **head, void *value);
void *linked_list_pop(ListNode **head);
void *linked_list_peek(ListNode *head);
void linked_list_push_front(ListNode **head, void *value);
void *linked_list_pop_front(ListNode **head);
void *linked_list_peek_front(ListNode *head);
void linked_list_free(ListNode **head, void (*destroy_function)(void *value));

#endif