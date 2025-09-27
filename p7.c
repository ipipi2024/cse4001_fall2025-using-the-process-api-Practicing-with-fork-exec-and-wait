#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("hello (pid:%d)\n", (int)getpid());

    pid_t rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child (pid:%d)\n", (int)getpid());
        close(STDOUT_FILENO);  // Close the file descriptor
        printf("This won't be displayed\n");
        exit(0);
    } else {
        pid_t rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int)getpid());
    }

    return 0;
}