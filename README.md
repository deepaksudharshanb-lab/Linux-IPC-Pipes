# Linux-IPC--Pipes
Linux-IPC-Pipes


# Ex03-Linux IPC - Pipes

# AIM:
To write a C program that illustrate communication between two process using unnamed and named pipes

# DESIGN STEPS:

### Step 1:

Navigate to any Linux environment installed on the system or installed inside a virtual environment like virtual box/vmware or online linux JSLinux (https://bellard.org/jslinux/vm.html?url=alpine-x86.cfg&mem=192) or docker.

### Step 2:

Write the C Program using Linux Process API - pipe(), fifo()

### Step 3:

Testing the C Program for the desired output. 

# PROGRAM:

## C Program that illustrate communication between two process using unnamed pipes using Linux API system calls


```
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char message[] = "Hello";
    char buffer[100];
    pipe(fd);  // Create pipe
    pid = fork();
    
    if(pid == 0) {
        // Child - read from pipe
        close(fd[1]);  // Close write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);
        close(fd[0]);
    }
    else {
        // Parent - write to pipe
        close(fd[0]);  // Close read end
        write(fd[1], message, strlen(message)+1);
        printf("Parent wrote: %s\n", message);
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
```


## OUTPUT
![Alt text](<Screenshot at 2026-03-19 03-51-36.png>)

## C Program that illustrate communication between two process using named pipes using Linux API system calls

```
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
```



## OUTPUT
![Alt text](<Screenshot at 2026-03-19 03-58-39.png>)

# RESULT:
The program is executed successfully.
