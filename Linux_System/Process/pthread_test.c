#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int thread_args[3] = {0, 1, 2};

void *Thread(void *arg) {

    int i;

    for(i = 0; i < 3; i++) 
        printf("thread %d : %dth iteration\n", *(int*)arg, i);

    pthread_exit(0);
}

void main(void) {

    int i, clock_get;

    pthread_t thread[3];

    for(i = 0; i < 3; i++) 
        pthread_create(&thread[i], NULL, Thread, (void *)&thread_args[i]);

    pthread_exit(*Thread);

    return 0;
}
