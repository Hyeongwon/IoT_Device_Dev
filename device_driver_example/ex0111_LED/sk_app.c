#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termio.h>
#include "sk.h"

int main(void) {

	int retn;
	int fd;
	
	//char buf[100] = "write...\n";
	//char buf[100] = {0};
	int flag = 0;

	fd = open("/dev/SK", O_RDWR);
	printf("fd = %d\n", fd);

	if(fd < 0) {

		perror("/dev/SK error");
		exit(-1);
	
	} else 
		printf("SK has been detected ...\n");
	
	//write
	//retn = write(fd, buf, 10);
	//printf("\nSize of written data : %d\n", retn);
	
	//read 
	//retn = read(fd, buf, 20);
	//printf("\ndata : %s\n", buf);

	getchar();

	/* fd가 가르키고 있는 파일에 0, flag라는 주소를 전달한다. */
	ioctl(fd, SK_LED_ON, flag); getchar();
	ioctl(fd, SK_LED_OFF, flag); getchar();
	ioctl(fd, SK_LED_ON, flag); getchar();
	ioctl(fd, SK_LED_OFF, flag); getchar();
	ioctl(fd, SK_LED_ON, flag); getchar();
	ioctl(fd, SK_LED_OFF, flag); getchar();
	ioctl(fd, SK_LED_ON, flag); getchar();
	ioctl(fd, SK_LED_OFF, flag); getchar();
	ioctl(fd, SK_LED_ON, flag); getchar();
	
	close(fd);

	return 0;
}
