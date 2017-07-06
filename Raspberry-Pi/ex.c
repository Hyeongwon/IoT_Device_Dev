#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {

    int fd = open("/dev/mem", O_RDWR);
    unsigned int* gpio_regs = 
        mmap(NULL, 4096, PROT_READ|PROT_WRITE, 
                MAP_SHARED, fd, 0x3F200000);

    printf("gpio_regs = %p\n", gpio_regs);

    gpio_regs[1] &= ~(0x7 << 9);
    gpio_regs[1] |= (0x1 << 9);
    
    while(1) {
        
        gpio_regs[7] |= 1 << 23;
    }

    munmap(gpio_regs, 4096);

    close(fd);

    return 0;
}
