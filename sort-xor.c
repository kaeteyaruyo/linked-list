#include "sort-list.h"

struct __list {
    int data;
    struct __list *addr;
};

list * xor
    (list * a, list *b) {
        return (list *) ((unsigned long) (a) ^ (unsigned long) (b));
    }

    list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start;
    list *right = start->addr;
    left->addr = NULL;
    right->addr = xor(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = xor(NULL, left->addr);
            if (next) {
                next->addr = xor(left, next->addr);
            }

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = xor (xor(merge->addr, NULL), left);
                left->addr = xor(merge, NULL);
                merge = left;
            }
            left = next;
        } else {
            list *next = xor(NULL, right->addr);
            if (next) {
                next->addr = xor(right, next->addr);
            }

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = xor (xor(merge->addr, NULL), right);
                right->addr = xor(merge, NULL);
                merge = right;
            }
            right = next;
        }
    }

    return start;
}

void insert_node(list **l, int d)
{
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if (!(*l)) {
        tmp->addr = NULL;
    } else {
        (*l)->addr = xor(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l)
{
    while (l) {
        list *next = l->addr;
        if (next) {
            next->addr = xor(next->addr, l);
        }
        free(l);
        l = next;
    }
}

void print_list(list *l)
{
    list *prev = NULL;
    while (l) {
        printf("%d\n", l->data);
        list *curr = l;
        l = xor(prev, l->addr);
        prev = curr;
    }
}
