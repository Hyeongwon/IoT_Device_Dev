#if 0
#include <stdio.h>
#include <string.h>

void callee(const char arr[], const char** reply) { // 1. 리턴타입을 완성하여 동작하게 합니다.
        static const char arr_reply[] = "Hello! caller, I'm fine";
            printf("%s\n", arr);
                *reply = arr_reply;
}

int main() { // caller
        const char arr[] = "Hello! callee, How are you?";
            const char *reply;
                callee(arr, &reply); 
                    printf("%s\n", reply);
}


#endif

#if 0
#include <stdio.h>
#include <string.h>

void callee(const char aarr[][20], const char (** reply)[20])  { // 2. 리턴타입을 완성하여 동작하게 합니다.
        static const char aarr_reply[][20] = {"Hello! callee,", " I'm fine"};
            for(int i=0;i<2;i++)
                        printf("%s", aarr[i]);
                printf("\n");
                    *reply = aarr_reply;
}

int main() { // caller
        const char aarr[][20] = {"Hello! caller,", " How are you?"};
            const char (*aarr_reply)[20];
                callee(aarr, &aarr_reply); // 2. 리턴타입을 완성하여 동작하게 합니다.
                    for(int i=0;i<2;i++)
                                printf("%s", aarr_reply[i]);
                        printf("\n");
}

#endif

#if 0
#include <stdio.h>
#include <string.h>

void callee(const char *parr[], const char*** reply) {// 3. 리턴타입을 완성하여 동작하게 합니다.
        static const char *parr_reply[] = {"Hello! caller,", " I'm fine"};
            for(int i=0;i<2;i++)
                        printf("%s", parr[i]);
                printf("\n");
                    *reply = parr_reply;
}

int main() { // caller
        const char *parr[] = {"Hello! callee,", " How are you?"};
            const char **reply;
                callee(parr, &reply);// 3. 리턴타입을 완성하여 동작하게 합니다.
                    for(int i=0;i<2;i++)
                                printf("%s", reply[i]);
                        printf("\n");
}

#endif

#if 1
#include <stdio.h>
#include <string.h>


void func() {
        printf("Hello! callee, How are you?\n");
}

void func_reply() {
        printf("Hello! caller, I'm fine\n");
}

void callee(void (*func)(), void (**reply)()) {// 4. 리턴타입을 완성하여 동작하게 합니다.
        func();
            *reply = func_reply;
}

int main() { // caller  
        void (*fp)();
            callee(func, &fp);// 4. 리턴타입을 완성하여 동작하게 합니다.    
                fp();
}

#endif
