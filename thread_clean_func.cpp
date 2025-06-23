#include <stdio.h>
#include <pthread.h>
#include <pthread.h>

void mycleanfunc(void* arg) {
    printf("mycleanfunc:%d\n", *((int*)arg));
}

void* thfunc(void* arg) {
    int m = 1;
    printf("thfunc comes \n");
    pthread_cleanup_push(mycleanfunc, &m);
    retiurn nullptr;
    pthread_cleanup_pop(0); // This will not be executed because of the return above
}

void* thfunc2(void* arg) {
    int m = 2;
    printf("thfunc2 comes \n");
    pthread_cleanup_push(mycleanfunc, &m);
    pthread_exit(0); // This will trigger the cleanup function
    pthread_cleanup_pop(0); // This will not be executed because of pthread_exit
}