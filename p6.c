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
        printf("Child first!\n");

        // Cause segmentation fault
        int *p = NULL;
        *p = 42;

        exit(0); // child should never reach here
    } else {
        int status;
        pid_t rc_wait = waitpid(rc, &status, 0);
        if (rc_wait == -1) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        }

        printf("parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int)getpid());

        if (WIFEXITED(status)) {
            printf("Child exited normally with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child terminated by signal %d\n", WTERMSIG(status));
        } else {
            printf("Child did not exit normally\n");
        }

        printf("Then parent\n");
    }

    return 0;
}
