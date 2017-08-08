#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 30

int main(int argc, char **argv) {

    static const char mesg[] = "www.google.com";
    char buf[BUFSIZE];
    size_t rcount, wcount;
    int pipefd[2];

    size_t len;

    if( pipe(pipefd) < 0) {

        fprintf(stderr, "%s : pipe failed : %s\n", argv[0], strerror(errno));
        exit(1);
    }

    printf("Read end = fd %d, write end = fd %d\n", pipefd[0], pipefd[1]);

    len = strlen(mesg);

    if((wcount = write(pipefd[1], mesg, len)) != len) {

        fprintf(stderr, "%s : write failed : %s\n", argv[0], strerror(errno));
        exit(1);
    }

    if((rcount = read( pipefd[0], buf, BUFSIZE)) != wcount) {

        fprintf(stderr, "%s : read failed : %s\n", argv[0], strerror(errno));
        exit(1);
    }

    buf[rcount] = '\0';

    printf("Read <%s> from pipe \n", buf);
    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}

