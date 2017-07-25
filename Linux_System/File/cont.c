#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char **argv) {

    int return_stat;
    char *file_name;
    struct stat file_info;

    mode_t file_mode;

    if(argc != 2) {

        printf("Usage : ./file_info [file name]\n");
        exit(0);
    }

    file_name = argv[1];

    if((return_stat = stat(file_name, &file_info)) == 1) {

        perror("Error : ");
        exit(0);
    }
    
    file_mode = file_info.st_mode;
    printf("file name : %s\n", file_name);
    printf("==============================\n");
    printf("file type : ");

    if(S_ISREG(file_mode))
        printf("정규파일\n");
    else if(S_ISLNK(file_mode))
        printf("symbolic link\n");
    else if(S_ISDIR(file_mode))
        printf("dir\n");
    else if(S_ISCHR(file_mode))
        printf("char device\n");
    else if(S_ISBLK(file_mode))
        printf("block device\n");
    else if(S_ISFIFO(file_mode))
        printf("FIFO\n");
    else if(S_ISSOCK(file_mode))
        printf("Socket\n");

    printf("OWNER : %d\n", file_info.st_uid);
    printf("GROUP : %d\n", file_info.st_gid);
    printf("dev : %d\n", file_info.st_dev);
    printf("inode : %d\n", file_info.st_ino);
    printf("FILE SIZE IS : %d\n", file_info.st_size);
    printf("Last read time : %d\n", file_info.st_atime);
    printf("lat modify time : %d\n", file_info.st_mtime);
    printf("hard linked file number : %d\n", file_info.st_nlink);

    return 0;
}
