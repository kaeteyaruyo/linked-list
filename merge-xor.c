#include<stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct __list {
    int data;
    struct __list *addr;
} list;

list *xor(list *a, list *b) {
    return (list *)((unsigned long)(a) ^ (unsigned long)(b));
}

list *sort(list *start){
    // If there is no node or only one node, just return
    if (!start || !start->addr)
        return start;

    // Store the first node to left, and other nodes to right
    list *left = start;
    list *right = start->addr;
    // This will also cut off start pointer
    left->addr = NULL;
    right->addr = xor(right->addr, left);

    // Sort left
    left = sort(left);
    // Sort right
    right = sort(right);

    // While there are still something in left or right, keep sorting
    for (list *merge = NULL; left || right; ) {
        // If there is nothing in right or
        // there are something in both but left one is smaller
        if (!right || (left && left->data < right->data)) {
            // Record next step, and remove left's first node from it
            list *next = xor(NULL, left->addr);
            if(next){
                next->addr = xor(left, next->addr);
            }

            // If it's first node in result, initialize merge,
            // also assign to start (for return later)
            if (!merge) {
                start = merge = left;
                merge->addr = NULL;
            }
            // If it's not first node, store to merge
            // and go to next position
            else {
                merge->addr = xor(xor(merge->addr, NULL), left);
                left->addr = xor(merge, NULL);
                merge = left;
            }
            // Walk to next position in left
            left = next;
        }
        // If there is nothing in left or
        // there are something in both but left one is not smaller
        // Comments similar to upside
        else {
            list *next = xor(NULL, right->addr);
            if(next){
                next->addr = xor(right, next->addr);
            }

            if (!merge) {
                start = merge = right;
                merge->addr = NULL;
            }
            else {
                merge->addr = xor(xor(merge->addr, NULL), right);
                right->addr = xor(merge, NULL);
                merge = right;
            }
            right = next;
        }
    }
    // Return sorted result
    return start;
}

list *insert_head(list *next, int d){
    list *tmp = malloc(sizeof(list));
    tmp->data = d;

    if(!next){
        tmp->addr = NULL;
    }
    else{
        next->addr = xor(tmp, next->addr);
        tmp->addr = next;
    }
    return tmp;
}

void print(list *l){
    list *prev = NULL;
    while(l){
        printf("%d\n", l->data);
        list *curr = l;
        l = xor(prev, l->addr);
        prev = curr;
    }
}

void delete(list *l){
    while(l) {
        list *next = l->addr;
        if(next){
            next->addr = xor(next->addr, l);
        }
        free(l);
        l = next;
    }
}

int main(){
    list *l = NULL;
    int d;
    while(scanf("%d", &d) != EOF){
        l = insert_head(l, d);
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