#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start, unsigned size) {
    if (!start || !start->next)
        return start;

    list *left = start;
    list *tmp = start;

    for(int i = 1; i < size >> 1; ++i){
        tmp = tmp -> next;
    }
    list *right = tmp->next;
    tmp->next = NULL;

    left = sort(left, size >> 1);
    right = sort(right, (size + 1) >> 1);

    for (list *merge = NULL; left || right; ) {
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
    unsigned size = 0;
    struct timeval tv1, tv2;
    double time;

    int d;
    while(scanf("%d", &d) != EOF){
        l = insert(l, d);
        ++size;
    }

    gettimeofday(&tv1, NULL);
    l = sort(l, size);
    gettimeofday(&tv2, NULL);
    time = (tv2.tv_usec - tv1.tv_usec) * 0.001;

    printf("Elapsed time: %.3lf ms\n", time);
    delete(l);

    return 0;
}
