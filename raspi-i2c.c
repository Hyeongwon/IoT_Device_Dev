#include "raspi-i2c.h"

static inline
int i2c_smbus_access(int fd, char rw, uint8_t reg, 
        int size, i2c_smbus_data_u *data) {

    i2c_smbus_ioctl_data_s args = {

        .rw = rw,
        .reg = reg,
        .size = size,
        .data = data,
    };

    return ioctl(fd, I2C_SMBUS, &args);
}

int i2c_read_reg_byte(int fd, int reg) {

    i2c_smbus_data_u data = {0, };

    if(i2c_smbus_access(fd, I2C_SMBUS_READ,
                reg, I2C_SMBUS_BYTE_DATA, &data))
        return -1;
    else 
        return data.byte & 0xFF;
}

int i2c_read_reg_word(int fd, int reg) {

    i2c_smbus_data_u data = {0, };

    if(i2c_smbus_access(fd, I2C_SMBUS_READ, 
                reg, I2C_SMBUS_WORD_DATA, &data))
        return -1;
    else
        return data.word & 0xFFFF;
}

int i2c_write_reg_byte(int fd, int reg, int value) {

    i2c_smbus_data_u data = {0, };

    data.byte = (uint8_t)value;
    return i2c_smbus_access(fd, I2C_SMBUS_WRITE,
            reg, I2C_SMBUS_BYTE_DATA, &data);
}

int i2c_write_reg_word(int fd, int reg, int value) {

    i2c_smbus_data_u data = {0, };

    data.word = (uint16_t)value;

    return i2c_smbus_access(fd, I2C_SMBUS_WRITE, 
            reg, I2C_SMBUS_WORD_DATA, &data);
}
