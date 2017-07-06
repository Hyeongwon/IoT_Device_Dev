#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>

#include "raspi-i2c.h"

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define LED0_ON_L 0x6
#define LEDALL_ON_L 0xFA

const int pca9685_i2c_addr = 0x40;
const int freq = 50; // 50HZ - 20ms peroid

int main(void) {

    //setup pca9685
    int fd = open("/dev/i2c-1", O_RDWR);
    
    if(fd < 0) {
        printf("open error\n");
        return -1;
    }

    ioctl(fd, I2C_SLAVE, pca9685_i2c_addr);

    // Setup the chip. Enable auto-increment of registers
    int settings = i2c_read_reg_byte(fd, PCA9685_MODE1) & 0x7F;
    int auto_inc = settings | 0x20;
    i2c_write_reg_byte(fd, PCA9685_MODE1, auto_inc);

    // Set frequenct of PWM signals. Also ends sleep mode and starts PWM 
    // output

    int prescale = (int)(25000000.0f / (4096 * freq) - 0.5f);

    settings = i2c_read_reg_byte(fd, PCA9685_MODE1) & 0x7F;
    int sleep_bit = settings | 0x10;
    int wake = settings & 0xEF;
    int restart = wake | 0x80;

    //Go to sleep, set prescale ans wake up again.
    i2c_write_reg_byte(fd, PCA9685_MODE1, sleep_bit);
    i2c_write_reg_byte(fd, PCA9685_PRESCALE, prescale);
    i2c_write_reg_byte(fd, PCA9685_MODE1, wake);

    //Now wait a millisecond until oscillator finished stabilizing and restart PWM.
    usleep(1000);
    i2c_write_reg_byte(fd, PCA9685_MODE1, restart);

    // reset PCA9685 pwm
    i2c_write_reg_word(fd, LEDALL_ON_L, 0x00);
    i2c_write_reg_word(fd, LEDALL_ON_L + 2, 0x1000);

    // write pwm
    int on = 0;
    int off_begin = (4096 / 20.0) * 0.4;
    int off_end = (4096 / 20.0) * 2.6;
    int reg = LEDALL_ON_L;
    int angle;

    i2c_write_reg_word(fd, reg, on & 0x0FFF);

    while(1) {

        for(angle = off_begin; angle < off_end; angle++) {
            i2c_write_reg_word(fd, reg + 2, angle & 0x0FFF);
            printf("%d\n", angle);
            usleep(10000);
        }

        for(angle = off_end; angle > off_begin; angle--) {

            i2c_write_reg_word(fd, reg + 2, angle & 0x0FFF);
            printf("%d\n", angle);
            usleep(10000);
        }
    }
}

