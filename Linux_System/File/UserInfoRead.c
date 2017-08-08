#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

typedef struct {

    char name[28];
    int age;
    int sex;
    char hobby[28];
}userInfo;

int main(void) {

    int fd, fd1;
    userInfo myAddrBook;
    int buf;
    int dataSize;

   // fd = open("hello.txt", O_RDONLY);
    fd = open("num.dat", O_RDONLY);

    if( fd < 0) {

        perror("file open error");
        return 1;
    }

   // dataSize = sizeof(myAddrBook);
    dataSize = sizeof(int);
    /*
    printf("User Info =========================\n\n");

    while(read(fd, (void*)&myAddrBook, dataSize) == dataSize) {

        printf("name : %s\n", myAddrBook.name);
        printf("age : %d\n", myAddrBook.age);
        printf("sex : %s\n", myAddrBook.sex ? "Man" : "Woman");
        printf("hoddy : %s\n", myAddrBook.hobby);
        printf("=================================\n");
    }*/
    printf("%d\n", dataSize);
    printf("%d\n", read(fd, buf, dataSize));
    while(read(fd, (void*)&buf, dataSize) == dataSize) {

        printf("%d\n", buf);
    }

    close(fd);
    
    return 0;
}
