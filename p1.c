#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());
    int x = 100;  // Set initial value
    printf("Before fork: x = %d (pid:%d)\n", x, (int) getpid());
    
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child: initial x = %d (pid:%d)\n", x, (int) getpid());
        x = 200;  // Child changes x
        printf("child: after change x = %d (pid:%d)\n", x, (int) getpid());
    } else {
        // parent goes down this path (main)
        printf("parent: initial x = %d (pid:%d)\n", x, (int) getpid());
        x = 300;  // Parent changes x
        printf("parent: after change x = %d (pid:%d)\n", x, (int) getpid());
        
        // Wait for child to complete
        wait(NULL);
        printf("parent: final x = %d (pid:%d)\n", x, (int) getpid());
    }
    
    return 0;
}