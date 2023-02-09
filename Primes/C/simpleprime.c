#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000000

int main(void) {
    clock_t start, end;
    start = clock();
    
    char *sieve = (char *) calloc(MAX, sizeof(char));
    int count = 0;
    for (int i = 2; i < MAX; i++) {
        if (!sieve[i]) {
            count++;
            for (int j = 2 * i; j < MAX; j += i) {
                sieve[j] = 1;
            }
        }
    }
    
    end = clock();
    double time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f\n", time_elapsed);
    printf("Number of primes: %d\n", count);
    
    free(sieve);
    return 0;
}
