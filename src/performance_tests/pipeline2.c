/* Here we code various orders of operating on some
 * floats to witness the unexpected difference in timings
 * based on compiling strategy for pipelining.
 */

#include <sys/resource.h>
#include <stdio.h>

const SIZE  = 10000000;   // Allocation size 
const ITERS = 100;        // Main loop iterations

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
    printf("%s%.1f\n", text, mflops);
}

void main(void) {
    static float w, x, y, z;
    float time;
    int   i, j;

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE; i++) {
            w += 1.0;
            x += 1.0;
            y += 1.0;
            z += 1.0;
        }
    }
    stop("Case wxyz: ", 4, time);

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE; i++) {
            w += 1.0;
            y += 1.0;
            x += 1.0;
            z += 1.0;
        }
    }
    stop("Case wyxz: ", 4, time);

    time = start();
    for (j = 0; j < ITERS; j++) {
        for (i = 0; i < SIZE; i++) {
            w += 1.0;
            y += 1.0;
        }
    }
    stop("Case wy:   ", 2, time);
}
