#include "sort-list.h"

struct __list {
    int data;
    struct __list *next;
};

list *sort(list *start)
{
    if (!start || !start->next)
        return start;

    list *left, *right, *tmp;
    left = right = tmp = start;

    while (right && right->next) {
        right = right->next->next;
        tmp = tmp->next;
    }
    right = tmp->next;
    tmp->next = NULL;

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            if (!merge) {
                start = merge = left;
            } else {
                merge->next = left;
                merge = merge->next;
            }
            left = left->next;
        } else {
            if (!merge) {
                start = merge = right;
            } else {
                merge->next = right;
                merge = merge->next;
            }
            right = right->next;
        }
    }
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
