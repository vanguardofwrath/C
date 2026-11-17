#ifndef MY_LINKED_LIST_H
#define MY_LINKED_LIST_H

typedef struct MyListNode
{
    void *value;
    struct MyListNode *next;
} MyListNode;

void my_linked_list_push(MyListNode **head, void *value);
void *my_linked_list_pop(MyListNode **head);
void *my_linked_list_peek(MyListNode *head);
void my_linked_list_push_front(MyListNode **head, void *value);
void *my_linked_list_pop_front(MyListNode **head);
void *my_linked_list_peek_front(MyListNode *head);
void my_linked_list_free(MyListNode **head, void (*destroy_function)(void *value));

#endif