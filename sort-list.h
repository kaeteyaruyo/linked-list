#include <stdio.h>
#include <stdlib.h>

typedef struct __list list;

/* Sort linked list in ascending order. */
list *sort(list *start);

/* insert_node one node to list l with data d. */
void insert_node(list **l, int d);

/* delete_list entire list l. */
void delete_list(list *l);

/* print_list entire list l. */
void print_list(list *l);