#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc == 2) {
        for (int i = 0; i < atoi(argv[1]); ++i) {
            printf("%d\n", rand());
        }
    } else {
        printf(
            "Random number generator\nUsage: %s N (N for number of random "
            "number)\n",
            argv[0]);
    }
    return 0;
}