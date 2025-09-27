#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // Open file before fork
    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    
    printf("File descriptor: %d\n", fd);
    
    if (fork() == 0) {
        // Child process
        write(fd, "Child wrote this\n", 17);
        close(fd);
    } else {
        // Parent process  
        write(fd, "Parent wrote this\n", 18);
        wait(NULL); // Wait for child
        close(fd);
        
        // Show what's in the file
        printf("\nFile contents:\n");
        system("cat test.txt");
    }
    
    return 0;
}