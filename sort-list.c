#include "sort-list.h"
#include <sys/time.h>
unsigned long long getTime(struct timeval tv)
{
    return (unsigned long long) tv.tv_sec * 1000000ULL +
           (unsigned long long) tv.tv_usec;
}

int main()
{
    list *l = NULL;
    int d;
    struct timeval tv1, tv2;
    unsigned long long time;
    while (scanf("%d", &d) != EOF) {
        insert_node(&l, d);
    }

    gettimeofday(&tv1, NULL);
    l = sort(l);
    gettimeofday(&tv2, NULL);
    time = getTime(tv2) - getTime(tv1);

    printf("%.3lf\n", (double) (time * 0.001));
    delete_list(l);

    return 0;
}
