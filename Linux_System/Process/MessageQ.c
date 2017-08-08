#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
//#include "linux/prink.h"

mqd_t mq;
pthread_t thread1, thread2;

void send_thread(void) {

    char c = 'A';

    unsigned int prio = 0;
    struct timespec ts;
    printf("!!!\n");
    while(1) {

        printf("S(%c, prio = %d)\n", c, prio);

        mq_send(mq, &c, sizeof(c), prio);

        if(++c > 'Z') break;
        if(++prio > 10) prio = 0;
    }
}

void recv_thread(void) {

    char msg[64];
    int len;
    unsigned int prio = 0;

    struct mq_attr mq_attr;

    mq_attr.mq_maxmsg = 3;
    mq_attr.mq_msgsize = 10;
    mq_attr.mq_flags = 0;

    mq = mq_open("/hjqueue", O_RDWR | O_CREAT, 0, &mq_attr);

    while(1) {

        len = mq_receive(mq, msg, sizeof(msg), &prio);

        if(len > 0) {
            
            msg[len] = '\0';
            printf( "R(%s, prio = %d)\n", msg, prio);
        }
    }
}

int main(void) {

    pthread_attr_t attr;
    struct sched_param param;
    pthread_attr_init(&attr);

   // printf("@@@@\n");
    param.sched_priority = 110;
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&thread1, &attr, (void *(*)(void *))recv_thread, NULL);
   // printf("!!!\n");
    param.sched_priority = 120;
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&thread2, &attr, (void *(*)(void *))send_thread, NULL);

    pthread_exit(0);
}

