#if 0
#include <stdio.h>
#include <string.h>

void callee(char *arr) { // 1. 매개변수를 완성하여 동작하게 합니다.
        printf("%s\n", arr);
            strcpy(arr, "Hello! caller, I'm fine");
}

int main() { // caller
        char arr[] = "Hello! callee, How are you?";
        callee(arr);
        printf("%s\n", arr);
}

#endif

#if 0
#include <stdio.h>
#include <string.h>

void callee(char (*aarr)[20]) { // 2. 매개변수를 완성하여 동작하게 합니다.
       
        int i = 0;
        for(i=0;i<2;i++)
                    printf("%s", aarr[i]);
            printf("\n");
            strcpy(aarr[0], "Hello! caller,");
            strcpy(aarr[1], " I'm fine");
}

int main() { // caller
        char aarr[][20] = {"Hello! callee,", " How are you?"};
        int i = 0;
            callee(aarr);
                for(i=0;i<2;i++)
                            printf("%s", aarr[i]);
                    printf("\n");
}

#endif

#if 0
#include <stdio.h>
#include <string.h>

void callee(const char **parr) { // 3. 매개변수를 완성하여 동작하게 합니다.
        int i;
        for(i=0;i<2;i++)
                    printf("%s", parr[i]);
            printf("\n");
                parr[0] = "Hello! caller,";
                    parr[1] = " I'm fine";
}

int main() { // caller
        const char *parr[] = {"Hello! callee,", " How are you?"};
        callee(parr);
        int i;
         for(i=0;i<2;i++)
           printf("%s", parr[i]);
         printf("\n");
}

#endif

#if 1
#include <stdio.h>
#include <string.h>

void func(void) {
        printf("Hello! callee, How are you?");
}

void callee(void (*func)(void)) { // 4. 매개변수를 완성하여 동작하게 합니다.
        func();
}

int main() { // caller  
        callee(func);   
}

#endif

