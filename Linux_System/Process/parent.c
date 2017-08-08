// exec.c
#include <unistd.h>

int main() {
    
    execl("./file", "file", "a", "b", NULL);
}


