/* Here are looking at threading in a compute loop
 * to demonstrate false cache line sharing and 
 * its devastating effects, which is essentially
 * cache line contention.
 */

#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

const THREADS = 4;            // Number of threads
const ITERS   = 100000000;    // Number of iterations

struct thr {
    float *a;
    int   pos, size;
};

float start(void) {
    struct timeval t;
    struct rusage  u;

    getrusage(RUSAGE_SELF, &u);
    t = u.ru_utime; 
    return (float)t.tv_sec + 1.0e-6 * t.tv_usec;
}

void stop(char *text, float t) {
    float time, mflops;

    time = start() - t;
    mflops = 1.0e-6 * (float)THREADS * (float)ITERS / time;
    printf("%s %.1f\n", text, mflops);
}

void *compute(void *param) {
    float *a;
    int i, p, s;
  
    struct thr *th = (struct thr *)param;
 
    a = (*th).a; 
    p = (*th).pos;
    s = (*th).size;

    for (i = 0; i < s; i++) {
        a[p] += 1.0;
    }
}

void main(void) {
    float time, *a;
    int   i;
    pthread_t t[4];
    struct thr th[4];

    posix_memalign((void *)&a, 64, 100 * THREADS * sizeof(float));

    time = start();
    for (i = 0; i < THREADS; i++) {
        th[i].a = a;
        th[i].pos = i;
        th[i].size = ITERS;
        pthread_create(&t[i], NULL, &compute, &th[i]);
    }
    for (i = 0 ; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }
    stop("Same cache line:      ", time);

    time = start();
    for (i = 0; i < THREADS; i++) {
        th[i].a = a;
        th[i].pos = i * 64;
        th[i].size = ITERS;
        pthread_create(&t[i], NULL, &compute, &th[i]);
    }
    for (i = 0 ; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }
    stop("Different cache line: ", time);

    free(a);
}
