#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>

int thread_args[3] = {0, 1, 2};

void *Thread(void *arg) {

    int i;

    for(i = 0; i < 3; i++) 
        printf("thread %d : %dth iteration\n", *(int*)arg, i);

    pthread_exit(0);
}

void main(void *arg) {

    int i;

    pthread_t thread[3];
    struct sched_param param;    
    pthread_attr_t thread_attrs;
    for(i = 0; i < 3; i++) {

        pthread_attr_init(&thread_attrs);
        pthread_attr_setschedpolicy(&thread_attrs, SCHED_RR);
        param.sched_priority = 50;
        pthread_attr_setschedparam(&thread_attrs, &param);
        pthread_create(&thread[i], NULL, Thread, (void *)&thread_args[i]);
    }

    pthread_exit(0);

    return 0;
}
