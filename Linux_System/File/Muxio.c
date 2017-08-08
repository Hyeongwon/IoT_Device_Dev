#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void) {

    int fd[2];
    int i, n, state;

    char buf[255];

    struct timeval tv;

    fd_set readfds, writefds;
    
    fd[0] = open("/tmp/testfile1", O_RDONLY);
    fd[1] = open("/tmp/testfile2", O_RDONLY);

    if( fd[0] == -1 ) {

        perror("file open error1 : ");
        exit(0);
    }

    if( fd[1] == -1) {

        perror("file open error2 : ");
        exit(0);
    }

    memset(buf, 0x00, 255);

    for(;;) {

        FD_ZERO(&readfds);
        FD_SET(fd[0], &readfds);
        FD_SET(fd[1], &readfds);

        state = select(fd[1] + 1, &readfds, NULL, NULL, NULL);

        switch(state) {

            case -1:
                perror("select error : ");
                exit(0);
                break;

            default:
                
                for(i = 0; i < 2; i++) {

                    if(FD_ISSET(fd[i], &readfds)) {
                             read(fd[i], buf, 255);
                       // while(( n = read(fd[i], buf, 255)) > 0 )
                            printf("(%d) [%d] %s", state, i, buf);
                    }
                }

                memset(buf, 0x00, 255);
                break;
        }

        usleep(1000);
    }
}
