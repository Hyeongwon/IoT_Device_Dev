#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <unistd.h>

#define FILENAME "/dev/spidev0.0"

int main(void) {
    
    uint8_t mode, lsb, bits;
    uint32_t speed;

    int fd = open(FILENAME, O_RDWR);

    if(fd < 0) {

        printf("open error\n");
        return -1;
    }

    ioctl(fd, SPI_IOC_RD_MODE, &mode);
    ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb);
    ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

    printf("%s\n", FILENAME);
    printf(" mode :\t%d\n", mode);
    printf(" lsb:\t%d\n", lsb);
    printf(" bpw:\t%d\n", bits);
    printf(" speed:\t%d Hz max\n", speed);

    close(fd);
    return 0;
}
