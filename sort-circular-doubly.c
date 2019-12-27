#include "sort-list.h"

struct __list {
    int data;
    struct __list *prev, *next;
};

list *sort(list *start)
{
    if (!start || start->next == start->prev)
        return start;

    list *left = start;
    list *right = left->next;
    right->prev = left->prev;
    right->prev->next = right;
    left->prev = left;
    left->next = left;

    left = sort(left);
    right = sort(right);

    left->prev->next = NULL;
    right->prev->next = NULL;
    list *merge;
    for (merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge->next->prev = merge;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge->next->prev = merge;
                merge = merge->next;
            }
            right = right->next;
        }
    }

    merge->next = start;
    start->prev = merge;

    return start;
}

void insert_node(list **l, int d)
{
    list *tmp = malloc(sizeof(list));
    tmp->data = d;
    if (!(*l)) {
        tmp->prev = tmp;
        tmp->next = tmp;
    } else {
        tmp->prev = *l;
        tmp->next = (*l)->next;
        (*l)->next->prev = tmp;
        (*l)->next = tmp;
    }
    *l = tmp;
}

void delete_list(list *l)
{
    l->prev->next = NULL;

    list *tmp;
    while (l) {
        tmp = l->next;
        free(l);
        l = tmp;
    }
}

void print_list(list *l)
{
    list *tmp = l;
    while (tmp != l) {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }
}
