#ifndef _RASPI_I2C_H
#define _RASPI_I2C_H_

#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>

#define I2C_SMBUS 0x0720
#define I2C_SLAVE 0x0703

#define I2C_SMBUS_READ 1
#define I2C_SMBUS_WRITE 0

#define I2C_SMBUS_BYTE_DATA 2
#define I2C_SMBUS_WORD_DATA 3

typedef union {
    uint8_t byte;
    uint16_t word;
}i2c_smbus_data_u;

typedef struct {
    char rw;
    uint8_t reg;
    int size;
    i2c_smbus_data_u *data;
}i2c_smbus_ioctl_data_s;

int i2c_read_reg_byte(int fd, int reg);
int i2c_read_reg_word(int fd, int reg);
int i2c_write_reg_byte(int fd, int reg, int value);
int i2c_write_reg_word(int fd, int reg, int value);

#endif // _RASPI_I2C_H_
