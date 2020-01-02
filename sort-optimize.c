#include "sort-list.h"
#ifndef MIN_SIZE
#define MIN_SIZE 32
#endif

struct __list {
    int data;
    struct __list *next;
};

int list_size = 0;
int subseq_num = 1;

list *sort_small(list *start)
{
    list *curr = start->next;
    start->next = NULL;

    while (curr) {
        list *next = curr->next;
        list *pos = start, *prev = NULL;
        while (pos && pos->data < curr->data) {
            prev = pos;
            pos = pos->next;
        }

        if (prev)
            prev->next = curr;
        else
            start = curr;

        curr->next = pos;
        curr = next;
    }

    return start;
}

list *sort(list *start)
{
    if (!start || !start->next)
        return start;

    if (list_size / subseq_num <= MIN_SIZE)
        return sort_small(start);

    list *left, *right, *tmp;
    left = right = tmp = start;

    while (right && right->next) {
        right = right->next->next;
        tmp = tmp->next;
    }
    right = tmp->next;
    tmp->next = NULL;

    subseq_num *= 2;
    left = sort(left);
    right = sort(right);
    subseq_num /= 2;

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
    ++list_size;
}

void delete_list(list *l)
{
    list *tmp;
    while (l) {
        tmp = l->next;
        free(l);
        l = tmp;
    }
    list_size = 0;
}

void print_list(list *l)
{
    while (l) {
        printf("%d\n", l->data);
        l = l->next;
    }
}
