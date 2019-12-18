#include "sort-list.h"
#include <sys/time.h>

int main()
{
    list *l = NULL;
    int d;
    while (scanf("%d", &d) != EOF) {
        insert_node(&l, d);
    }

    struct timeval tv1, tv2;
    double time;
    gettimeofday(&tv1, NULL);
    l = sort(l);
    gettimeofday(&tv2, NULL);
    time = (tv2.tv_usec - tv1.tv_usec) * 0.001;

    printf("Elapsed time: %.3lf ms\n", time);
    delete_list(l);

    return 0;
}
