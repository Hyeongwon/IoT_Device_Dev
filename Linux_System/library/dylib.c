#include <stdio.h>
#include <dlfcn.h>

int main() {

    int a, b;
    a = 100;
    b = 50;
    
    void *handle;
    char *error;
    int (*result)(int, int);
    int (*diff)(int , int);
    
    handle = dlopen("libmylib.so.1", RTLD_NOW);
    if(!handle) {

        printf("open error\n");
        return 1;
    }

    result = dlsym(handle, "sum");
    diff = dlsym(handle, "diff");

    if( (error = dlerror() ) != NULL) {

        fputs(error, stderr);
        return 1;
    }
    else {

        printf("sum : %d\n", result(a, b));
        printf("diff : %d\n", diff(a, b));
    }

    dlclose(handle);
    return 0;
}

