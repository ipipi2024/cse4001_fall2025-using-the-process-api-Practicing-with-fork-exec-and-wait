#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello (pid:%d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        printf("child (pid:%d)\n", (int) getpid());

        // args as array/vector
        char *args[] = {"ls", NULL};
        char *args2[] = {"printenv", NULL};

        // Common custom environment for execle/execvpe
        char *env[] = {"MYVAR=HELLO_WORLD", NULL};

        //1. Passing argument as a list of parameters
        // execl("/bin/ls", "ls",NULL);

        //2. passing argument as an array
        // execv("/bin/ls", args);

        //3. passing argument as list parameter with p so it searchs for $PATH environment variable
        // execlp("ls", "ls", NULL);

        //4. passing argument as array with p
        // execvp("ls", args);

        //5. passing argument with custom environmental variable
        // execle("/usr/bin/printenv", "printenv", NULL, env);

        //6. passing argument as array  with cutome environment variable and search path
        execvpe("printenv", args2, env);
        


        // If exec is successful, this line will never run
        printf("this should not print!\n");
    } else {
        int rc_wait = wait(NULL);
        printf("parent of %d (rc_wait:%d) (pid:%d)\n",
               rc, rc_wait, (int) getpid());
    }

    return 0;
}
