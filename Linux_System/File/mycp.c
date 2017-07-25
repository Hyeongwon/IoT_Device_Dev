#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv) {

    char *file_name_ori;
    char *file_name_cp;
    
    char buf[1024];
    int fd_ori, fd_cp;
    int size;

    if(argc != 3) {

        printf("Usage : ./file_info [file_name]\n");
        exit(0);
    }

    file_name_ori = argv[1];
    file_name_cp = argv[2];

    fd_ori = open(file_name_ori, O_RDWR | O_CREAT, 1000);
    fd_cp = open(file_name_cp, O_RDWR | O_CREAT, 1000 | S_IWUSR);

    if(fd_ori < 0) {

        perror("error:");
        exit(0);
    }

    if(fd_cp < 0) {

        perror("error: cp");
        exit(0);
    }
    
    while( (size = read(fd_ori, buf, sizeof(buf))) > 0)
        write(fd_cp, buf, size);
      
    
   // printf("%s\n", buf);

    close(fd_ori);
    close(fd_cp);
    
    return 0;
}

