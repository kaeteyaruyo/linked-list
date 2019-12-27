#include "sort-list.h"
#define XOR(a, b) ((list *) ((unsigned long) (a) ^ (unsigned long) (b)))

struct __list {
    int data;
    struct __list *addr;
};

list *sort(list *start)
{
    if (!start || !start->addr)
        return start;

    list *left = start;
    list *right = start->addr;
    left->addr = NULL;
    right->addr = XOR(right->addr, left);

    left = sort(left);
    right = sort(right);

    for (list *merge = NULL; left || right;) {
        if (!right || (left && left->data < right->data)) {
            list *next = XOR(NULL, left->addr);
            if (next) {
                next->addr = XOR(left, next->addr);
            }

            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(XOR(merge->addr, NULL), left);
                left->addr = XOR(merge, NULL);
                merge = left;
            }
            left = next;
        } else {
            list *next = XOR(NULL, right->addr);
            if (next) {
                next->addr = XOR(right, next->addr);
            }

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            } else {
                merge->addr = XOR(XOR(merge->addr, NULL), right);
                right->addr = XOR(merge, NULL);
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
        (*l)->addr = XOR(tmp, (*l)->addr);
        tmp->addr = *l;
    }
    *l = tmp;
}

void delete_list(list *l)
{
    while (l) {
        list *next = l->addr;
        if (next) {
            next->addr = XOR(next->addr, l);
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
        l = XOR(prev, l->addr);
        prev = curr;
    }
}
