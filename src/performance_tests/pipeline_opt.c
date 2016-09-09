/* Here we hand code multiple levels of instruction
 * parallelism to demonstrate pipelining and compiler
 * optimization.
 */

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

const SIZE  = 10000000;     // Size to allocate
const ITERS = 100;          // Main loop iterations

float start(void) {
    struct timeval t;
    struct rusage  u;

    getrusage(RUSAGE_SELF, &u);
    t = u.ru_utime; 
    return (float)t.tv_sec + 1.0e-6 * t.tv_usec;
}

void stop(char *text, int k, float t) {
    float time, mflops;

    time = start() - t;
    mflops = 1.0e-6 * (float)k * (float)SIZE * (float)ITERS / time;
    printf("%s %.1f\n", text, mflops);
}

void main(void) {
    float time, *a;
    int   i, j;

    posix_memalign((void *)&a, 64, SIZE * sizeof(float));

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE - 3; i++) {
            a[i] += 1.0; 
            a[i] += 1.0; 
            a[i] += 1.0; 
            a[i] += 1.0; 
        }
    }
    stop("One instruction:   ", 4, time);

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE - 3; i++) {
            a[i] += 1.0; 
            a[i] += 1.0; 
            a[i+1] += 1.0; 
            a[i+1] += 1.0; 
        }
    }
    stop("Two instructions:  ", 4, time);

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE - 3; i++) {
            a[i] += 1.0; 
            a[i+1] += 1.0; 
            a[i+2] += 1.0; 
            a[i+3] += 1.0; 
        }
    }
    stop("Four instructions: ", 4, time);

    free(a);
}
