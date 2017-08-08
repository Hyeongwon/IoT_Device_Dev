#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(void) {

    int fd;
    fd = open("test.log", O_CREAT | O_WRONLY,0644);
    fd = dup2(fd, STDOUT);
    printf("Hello World %d\n", fd);
}
