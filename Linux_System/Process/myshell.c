#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    
    char command[20];
    char *option, *com;
    char dir[20] = "/bin/";
    int pid, i, j;
    int exit_num;
    
    while(1) {
        
        printf("myshell # ");
        gets(command);
        com = strtok(command, " ");
    
        while(com != NULL) {
       
            com = option;
            option = strtok(NULL, " ");
        }
        
        strcat(dir, command);
        
        pid = fork();

        if(pid == 0) {
            
            if(!strcmp(command, "exit")) exit(3);
        
            execl(dir, command, option, NULL);
     
        }
            
        else {
            wait(&exit_num);
            
            if(exit_num == 768) return 0;
           // else  execle("./myshell", NULL, NULL, NULL);   
        }
    }
    
}
       

       

   
