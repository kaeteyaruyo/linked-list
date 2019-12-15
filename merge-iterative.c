#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct __list {
    int data;
    struct __list *next;
} list;

list *sort(list *start) {
    if(!start) return NULL;

    // Start from second node if the list has more than one node
    list *curr = start->next;
    // Store sorted result in *start
    // At the beginning, there is one node in *start
    start->next = NULL;

    // Walk through the list, start from second node
    while(curr){
        // Record next step
        list *next = curr->next;

        // Find position to insert
        // We will insert curr to the middle of pos and prev
        list *pos = start, *prev = NULL;
        while(pos && pos->data < curr->data){
            prev = pos;
            pos = pos->next;
        }

        // If prev is not null, which means
        // the position is not at the start of the list,
        // then update prev's next
        if(prev){
            prev->next = curr;
        }
        // Else, which means the position is at the start of the list,
        // then we need to update start
        else{
            start = curr;
        }
        curr->next = pos;

        // Go to next node
        curr = next;
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
