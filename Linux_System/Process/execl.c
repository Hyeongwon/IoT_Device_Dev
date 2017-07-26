#include <unistd.h>

void main(void) {
    
    printf("before executing ls -l \n");
    execl("/bin/ls", "ls", "-l", (char *)0);
    printf("afrer executing ls -l \n");

    return 0;
}
