#include "sort-list.h"

struct __list {
    int data;
    struct __list *next;
};

list *sort(list *start)
{
    if (!start)
        return NULL;

    // Start from second node if the list has more than one node
    list *curr = start->next;
    // Store sorted result in *start
    // At the beginning, there is one node in *start
    start->next = NULL;

    // Walk through the list, start from second node
    while (curr) {
        // Record next step
        list *next = curr->next;

        // Find position to insert
        // We will insert curr to the middle of pos and prev
        list *pos = start, *prev = NULL;
        while (pos && pos->data < curr->data) {
            prev = pos;
            pos = pos->next;
        }

        // If prev is not null, which means
        // the position is not at the start of the list,
        // then update prev's next
        if (prev) {
            prev->next = curr;
        }
        // Else, which means the position is at the start of the list,
        // then we need to update start
        else {
            start = curr;
        }
        curr->next = pos;

        // Go to next node
        curr = next;
    }

    // Return sorted result
    return start;
}

void insert_node(list **l, int d)
{
    list *tmp = malloc(sizeof(list));
    tmp->data = d;
    tmp->next = *l;
    *l = tmp;
}

void delete_list(list *l)
{
    list *tmp;
    while (l) {
        tmp = l->next;
        free(l);
        l = tmp;
    }
}

void print_list(list *l)
{
    while (l) {
        printf("%d\n", l->data);
        l = l->next;
    }
}
