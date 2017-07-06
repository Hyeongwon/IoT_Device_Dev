#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
 
typedef unsigned int uint32_t;
 
int main() {
    
    int fd = open("/dev/mem", O_RDWR);
    uint32_t *gpio_regs =
        (uint32_t *)mmap(NULL, 0x1000, PROT_READ|PROT_WRITE,
                MAP_SHARED, fd, 0x3F200000);
    uint32_t *clk_regs =
        (uint32_t *)mmap(NULL, 0x1000, PROT_READ|PROT_WRITE,
                MAP_SHARED, fd, 0x3F101000);
    uint32_t *pwm_regs =
        (uint32_t *)mmap(NULL, 0x1000, PROT_READ|PROT_WRITE,
                MAP_SHARED, fd, 0x3F20C000);
    
    printf("gpip_regs = %p\n", *gpio_regs);                                     
    
    gpio_regs[1] &= ~(0x7 << 6);
    gpio_regs[1] |= (0x4 << 6);
    
    gpio_regs[1] &= ~(0x7 << 9);
    gpio_regs[1] |= (0x1 << 9);
    
    // 234 rbg;
    gpio_regs[0] &= ~(0x7 << 15);
    gpio_regs[0] |= (0x1 << 15);
    gpio_regs[0] &= ~(0x7 << 18);
    gpio_regs[0] |= (0x1 << 18);

    clk_regs[40] = 0x5A000020;
    
    usleep(10);
   // while(clk_regs[40]&0x80) {}

    clk_regs[41] = 0x5A013000;
    clk_regs[40] = 0x5A000011;
                                                                     
    pwm_regs[0] = 0;
    usleep(10);
    pwm_regs[4] = 1000-1;
    pwm_regs[5] = 500-1;
    pwm_regs[8] = 1000-1;
    pwm_regs[9] = 500-1;
    pwm_regs[0] = 0x8181;
    
    const int melody[] = {
        262, 294, 330, 349, 392, 440, 494, 523,
    };
   /* 
    while(1) {
        
        int i;

        for(i = 0; i < 1000; i++) {
            
            pwm_regs[9] = i;
            pwm_regs[5] = i;
            usleep(1000);
        }
    }
 */
    gpio_regs[10] |= 1 << 5;
    gpio_regs[10] |= 1 << 6;
    gpio_regs[10] |= 1 << 13;
    
    printf("%p\n", gpio_regs[7]);

    while(1) {
        int val;
        int i;
        scanf("%d", &val);
        
        gpio_regs[10] |= 1 << 5;
        gpio_regs[10] |= 1 << 6;
        gpio_regs[10] |= 1 << 13;

        if(val == 1) {
           gpio_regs[7] |= 1 << 5;
           printf("%x\n", gpio_regs[7]);
        } else if(val == 2) {
            gpio_regs[7] |= 1 << 6;
        } else if(val == 3) {
            gpio_regs[7] |= 1 << 13;
        } else if(val == 4) {
        } else if(val == 5) {
        } else if(val == 6) {
        } else if(val == 7) {
        } else if(val == 8) {
        }
        printf("val = %d\n", val);
        
        if(val <=  8) {
             pwm_regs[4] = (1000000/melody[val-1]);
             pwm_regs[5] = (1000000/melody[val-1] / 2);
             usleep(100000);
        }
    }
    /*
    while(1) {
        int duty;
        for(duty = 450; duty <= 2500; duty++) {
            pwm_regs[5] = duty - 1;
            pwm_regs[9] = duty - 1;
            usleep(1000);
        }

        pwm_regs[5] = 450 - 1;
        pwm_regs[9] = 450 - 1;
        usleep(5000000);
    }*/

    munmap(gpio_regs, 0x1000);
    munmap(clk_regs, 0x1000);
    munmap(pwm_regs, 0x1000);
                                                                                                                               
    close(fd);
                                                                                                                                                            
    return 0;
}
