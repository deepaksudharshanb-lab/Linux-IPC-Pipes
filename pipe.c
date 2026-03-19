#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>  // Added for wait()
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello";
    char buffer[100];
    
    pipe(fd);  // Create pipe
    pid = fork();
    
    if(pid == 0) {
        // Child process - reads from pipe
        close(fd[1]);  // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);
        close(fd[0]);
    } else if(pid > 0) {
        // Parent process - writes to pipe
        close(fd[0]);  // Close unused read end
        sleep(1);      // Allow child to close write end first [web:1][web:12]
        write(fd[1], message, strlen(message) + 1);
        printf("Parent wrote: %s\n", message);
        close(fd[1]);
        wait(NULL);    // Wait for child to complete [web:7]
    } else {
        perror("fork failed");
    }
    return 0;
}
