#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "errno.h"

using namespace std;
void* thfunc(void* arg) {
    int tm = 50;
    while(true) {
        cout << "thrfunc-left: " << tm << "S -- " << endl;
        sleep(1);
        tm--;
    }

    return nullptr;
}

int main(int argc, char* argv[]) {
    pthread_t tid;
    int res = pthread_create(&tid, nullptr, thfunc, nullptr);
    if(res != 0) {
        cerr << "Error creating thread: " << strerror(res) << endl;
        return 1;
    }

    sleep(5); // Let the thread run for a while
    int kill_rc = pthread_kill(tid, 0);
    if(kill_rc == ESRCH) {
        cout << "Thread has already ended." << endl;
    } else if(kill_rc == 0) {
        cout << "Thread is still running." << endl;
    } else if(kill_rc == EINVAL) {
        cerr << "Signal is invalid." << endl;
    } else {
        cerr << "The specified thread is still alive." << endl;
    }
}