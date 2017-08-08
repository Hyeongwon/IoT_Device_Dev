#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>

int main(void) {

    pid_t current_pid = getpid();
    int priority = getpriority(PRIO_PROCESS, current_pid);

    printf("Process : %d, priority: %d\n", current_pid, priority);

    for(;;) sleep(1);

    return 0;
}
