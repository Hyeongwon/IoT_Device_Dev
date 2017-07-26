#include <stdio.h>

int main(void) {

    unsigned int cnt = 0;

    while(1) {

        printf("%d: %d\n", getpid(), cnt);
        cnt++;
    }
}
