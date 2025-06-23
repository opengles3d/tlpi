#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

using namespace std;
static void on_signal_term(int sig) {
    cout << "Received signal " << sig << ", terminating thread." << endl;
    pthread_exit(nullptr);
}

void* thread_function(void* arg) {
    signal(SIGQUIT, on_signal_term);
    cout << "Thread started, waiting for termination signal..." << endl;
    
    // Simulate work
    int tm = 50;
    while(true) {
        cout << "thread_function is running, sleeping for " << tm << " milliseconds." << endl;
        sleep(1);
        tm--
    }
    return nullptr;
}

int main() {
    pthread_t thread;
    
    // Create a new thread
    if (pthread_create(&thread, nullptr, thread_function, nullptr) != 0) {
        cerr << "Error creating thread." << endl;
        return 1;
    }
    
    sleep(5); // Let the thread run for a while
    pthread_kill(thread, SIGQUIT); // Send termination signal to the thread
    // Wait for the thread to finish
    pthread_join(thread, nullptr);
    
    cout << "Thread has finished execution." << endl;
    return 0;
}