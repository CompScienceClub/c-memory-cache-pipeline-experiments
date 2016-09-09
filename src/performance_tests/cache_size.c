/* This uses timing to estimate the L1 and L2 cache
 * sizes. 
 */

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

const ITERS = 20;           // Loop iteration scaling
const START = 256;          // Min cache size (less than L1 size)
const STOP  = 33554432;     // Max cache size (more than L2 size)
const STEP  = 2;            // Geometric step
const MULT  = 64;           // Multiplier for skipping cache line

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
    mflops = 1.0e-6 * (float)STOP * (float)ITERS / time;
    printf("%d: %.1f\n", k, mflops);
}

void main(void) {
    float time, *a;
    int   i, j, k;

    posix_memalign((void *)&a, 64, STOP * sizeof(float));

    for (k = START; k < STOP + 1; k *= STEP) {
        time = start();
        for (i = 0; i < ITERS * STOP / k; i++) {
            for (j = 0; j < k; j++) {
                a[(j * MULT) & (k - 1)] += 1.0;   
            }
        }
        stop(k, time);
    }

    free(a);
}
