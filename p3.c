#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    if (fork() == 0) {
        // Child process
        printf("hello\n");
        exit(0);
    } else {
        // Parent process
        sched_yield(); // Yield CPU to let child run
        usleep(10000); // Small delay to be more certain
        printf("goodbye\n");
    }
    
    return 0;
}