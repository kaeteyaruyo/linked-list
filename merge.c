#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start) {
    // If there is no node or only one node, just return
    if (!start || !start->next)
        return start;

    // Store the first node to left, and other nodes to right
    list *left = start;
    list *right = left->next;
    // This will also cut off start pointer
    left->next = NULL;

    // Sort left
    left = sort(left);
    // Sort right
    right = sort(right);

    // While there are still something in left or right, keep sorting
    for (list *merge = NULL; left || right; ) {
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
                merge = merge->next;
            }
            right = right->next;
        }
    }
    // Return sorted result
    return start;
}

list *insert(list* l, int d){
    list *tmp = malloc(sizeof(list));
    tmp->data = d;
    tmp->next = l;
    return tmp;
}

void print(list *l){
    while(l){
        printf("%d\n", l->data);
        l = l->next;
    }
}

void delete(list *l){
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
