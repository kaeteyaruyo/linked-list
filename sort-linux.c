#include "sort-list.h"
#include "list.h"

struct __list {
    int data;
    struct list_head link;
};

list *sort(list *start)
{
    if (!start || list_empty(&start->link) || list_is_singular(&start->link))
        return start;

    LIST_HEAD(left);
    // To avoid unnecessary nodes duplication,
    // just use start as right
    list_move((start->link).next, &left);

    left = sort(list_entry(&left, list, link))->link;
    start->link = sort(start)->link;

    LIST_HEAD(merge);
    while (!(list_empty(&left) && list_empty(&start->link))) {
        if (list_empty(&start->link) ||
            (!list_empty(&left) &&
             list_entry(left.next, list, link)->data <
                 list_entry(start->link.next, list, link)->data)) {
            list_move_tail(left.next, &merge);
        } else {
            list_move_tail(start->link.next, &merge);
        }
    }
    list_splice(&merge, &start->link);
    return start;
}

void insert_node(list **l, int d)
{
    if (!(*l)) {
        (*l) = malloc(sizeof(list));
        INIT_LIST_HEAD(&(*l)->link);
    }
    list *tmp = malloc(sizeof(list));
    tmp->data = d;
    list_add(&tmp->link, &(*l)->link);
}

void delete_list(list *l)
{
    list *tmp;
    struct list_head *curr, *save;
    list_for_each_safe(curr, save, &l->link)
    {
        tmp = list_entry(curr, list, link);
        list_del(curr);
        free(tmp);
    }
}

void print_list(list *l)
{
    list *node;
    list_for_each_entry(node, &l->link, link) { printf("%d\n", node->data); }
}
