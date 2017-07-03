#if 0
#include <stdio.h>
#include <string.h>

const char* callee(const char arr[]) { // 1. 리턴타입을 완성하여 동작하게 합니다.
        static const char arr_reply[] = "Hello! caller, I'm fine";
            printf("%s\n", arr);
                return arr_reply;
}

int main() { // caller
        const char arr[] = "Hello! callee, How are you?";
            const char*  reply = callee(arr); // 1. 리턴타입을 완성하여 동작하게 합니다.
                printf("%s\n", reply);
}


#endif

#if 0
#include <stdio.h>
#include <string.h>

const char (*callee(const char aarr[][20]))[20]  { // 2. 리턴타입을 완성하여 동작하게 합니다.
        static const char aarr_reply[][20] = {"Hello! callee,", " I'm fine"};
            for(int i=0;i<2;i++)
                        printf("%s", aarr[i]);
                printf("\n");
                    return aarr_reply;
}

int main() { // caller
        const char aarr[][20] = {"Hello! caller,", " How are you?"};
          const char (*aarr_reply)[20] = callee(aarr);// 2. 리턴타입을 완성하여 동작하게 합니다.
                for(int i=0;i<2;i++)
                            printf("%s", aarr_reply[i]);
                    printf("\n");
}

#endif

#if 0
#include <stdio.h>
#include <string.h>

const char** callee(const char *parr[]) {// 3. 리턴타입을 완성하여 동작하게 합니다.
        static const char *parr_reply[] = {"Hello! caller,", " I'm fine"};
            for(int i=0;i<2;i++)
                        printf("%s", parr[i]);
                printf("\n");
                    return parr_reply;
}

int main() { // caller
        const char *parr[] = {"Hello! callee,", " How are you?"};
           const char ** parr_reply = callee(parr);// 3. 리턴타입을 완성하여 동작하게 합니다.
                for(int i=0;i<2;i++)
                            printf("%s", parr_reply[i]);
                    printf("\n");
}

#endif

#if 1
#include <stdio.h>
#include <string.h>


void func(void) {
        printf("Hello! callee, How are you?\n");
}

void func_reply(void) {
        printf("Hello! caller, I'm fine\n");
}

void (*callee (void(*func)()))(void) {// 4. 리턴타입을 완성하여 동작하게 합니다.
        func();
            return func_reply;
}

int main() { // caller  
        void (*fp)(void)  = callee(func);// 4. 리턴타입을 완성하여 동작하게 합니다.    
        fp();
}

#endif
