#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void intHandler(int signo) {

    printf("ctrl + c pressed\n");
}

void alarmHandler(int signo) {

    static int cnt;
    cnt++;
    printf("%d\n", cnt);
    alarm(1);
}

int main() {

    signal(SIGINT, intHandler);
    signal(SIGALRM, alarmHandler);

    while(1) {

        printf("loop\n");
        sleep(1);
    }
}


