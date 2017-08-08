#include <stdio.h>
#include <stdlib.h> //for system
#include <unistd.h> //for execl, fork
#include <wait.h> //for wait

int main() {

    int pid;
    pid = fork();

    if(pid < 0) {

        fprintf(stderr, "Fork Failed");
        exit(-1);

    }else if( pid == 0) {

        execl("/bin/ls", "ls", "-l", NULL);

    }else {

        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
    
    return 0;
}
