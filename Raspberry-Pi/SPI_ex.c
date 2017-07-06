#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "/dev/spidev0.0"

int main(void) {
    
    uint8_t mode, lsb, bits;
    uint32_t speed;

    int fd = open(FILENAME, O_RDWR);

    if(fd < 0) {

        printf("open error\n");
        return -1;
    }

    ioctl(fd, SPI_IOC_WR_MODE, &mode);
    ioctl(fd, SPI_IOC_WR_LSB_FIRST, &lsb);
    ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    
    /*
    printf("%s\n", FILENAME);
    printf(" mode :\t%d\n", mode);
    printf(" lsb:\t%d\n", lsb);
    printf(" bpw:\t%d\n", bits);
    printf(" speed:\t%d Hz max\n", speed);
    */

    {
        int adcChannel = 1;
        int adcValue = 0;
        unsigned char buf[3];

        const struct spi_ioc_transfer xfer = {

            .tx_buf = (unsigned long)buf,
            .rx_buf = (unsigned long)buf,
            .len = sizeof(buf),
            .delay_usecs = 0,
            .speed_hz = speed,
            .bits_per_word = bits,
        };

        while(1) {

            memset(buf, 0, sizeof(buf));

            buf[0] = 0x06 | ((adcChannel & 0x07) >> 2);
            buf[1] = ((adcChannel & 0x07) << 6);
            buf[2] = 0x00;

            ioctl(fd, SPI_IOC_MESSAGE(1), &xfer);

            buf[1] = 0x0F & buf[1];
            adcValue = ( buf[1] << 8 ) |  buf[2];
            printf("%d\n", sizeof(buf[1]));
            usleep(1000000);
            printf("adc0 Value = %u\n", adcValue);
        }
    }

    close(fd);
    return 0;
}
