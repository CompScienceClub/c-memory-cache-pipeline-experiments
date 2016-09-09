/* This uses timing to estimate the cache line size
 * and demonstrate effect of memory speed and processor
 * speed on numeric computation.
 */

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

const CACHE  = 16777216;    // Max cache size
const ROUNDS = 100;         // Rounds of test
const START  = 1;           // Starting step
const STOP   = 512;         // Ending step
const STEP   = 2;           // Geometric step size

float start(void) {
    struct timeval t;
    struct rusage  u;

    getrusage(RUSAGE_SELF, &u);
    t = u.ru_utime; 
    return (float)t.tv_sec + 1.0e-6 * t.tv_usec;
}

void stop(int k, float t) {
    float time, mflops;

    time = start() - t;
    mflops = 1.0e-6 * (float)ROUNDS * (float)CACHE / ((float)k * time);
    printf("%d: %.1f\n", k, mflops);
}

void main(void) {
    float time, mflops, *a;
    int   i, j, k;

    posix_memalign((void *)&a, 64, CACHE * sizeof(float));

    for (k = START; k < STOP; k *= STEP) {
        time = start();
        for (i = 1; i < ROUNDS; i++) {
            for (j = 0; j < CACHE; j+=k) {
                a[j] += 1.0;
            }
        }
        stop(k, time);
    }

    free(a);
}
