#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct __list {
    int data;
    struct __list *prev, *next;
} list;

list *sort(list *start) {
    // If there is no node or only one node, just return
    if (!start || start->next == start->prev)
        return start;

    // Store the first node to left, and other nodes to right
    list *left = start;
    list *right = left->next;
    // This will also cut off start pointer
    right->prev = left->prev;
    right->prev->next = right;
    left->prev = left;
    left->next = left;

    // Sort left
    left = sort(left);
    // Sort right
    right = sort(right);

    // Mark tail of list (for stop condition)
    left->prev->next = NULL;
    right->prev->next = NULL;
    list *merge;
    // While there are still something in left or right, keep sorting
    for (merge = NULL; left || right; ) {
        // If there is nothing in right or
        // there are something in both but left one is smaller
        if (!right || (left && left->data < right->data)) {
            // If it's first node in result, initialize merge,
            // also assign to start (for return later)
            if (!merge) {
                start = merge = left;
            }
            // If it's not first node, store to merge
            // and go to next position
            else {
                merge->next = left;
                merge->next->prev = merge;
                merge = merge->next;
            }
            // Walk to next position in left
            left = left->next;
        }
        // If there is nothing in left or
        // there are something in both but left one is not smaller
        // Comments similar to upside
        else {
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

    // Connect head and tail
    merge->next = start;
    start->prev = merge;
    // Return sorted result
    return start;
}

list *insert(list* l, int d){
    list *tmp = malloc(sizeof(list));
    tmp->data = d;
    if(!l){
        tmp->prev = tmp;
        tmp->next = tmp;
    }
    else{
        tmp->prev = l;
        tmp->next = l->next;
        l->next->prev = tmp;
        l->next = tmp;
    }
    return tmp;
}

void print(list *l, int clockwise){
    if(!l){
        printf("NULL\n");
        return;
    }

    list *tmp = l;
    do {
        printf("%d\n", tmp->data);
        if(clockwise)
            tmp = tmp->next;
        else
            tmp = tmp->prev;
    } while(tmp != l);
}

void delete(list *l){
    l->prev->next = NULL;

    list *tmp;
    while(l){
        tmp = l->next;
        free(l);
        l = tmp;
    }
}

int main(){
    list *l = NULL;
    int d;
    while(scanf("%d", &d) != EOF){
        l = insert(l, d);
    }
    struct timeval tv1, tv2;
    double time;

    gettimeofday(&tv1, NULL);
    l = sort(l);
    gettimeofday(&tv2, NULL);
    time = (tv2.tv_usec - tv1.tv_usec) * 0.001;

    printf("Elapsed time: %.3lf ms\n", time);
    delete(l);

    return 0;
}
