//Que 3.3:-Write  a  program  that  opens  a  file  (with  theopen()system  call)  and  then  callsfork()to  create  a new  process.  Can  both  the  child  and  parent  access  the  file  descriptor  returned  byopen()?  What happens  when they  are  writing  to  the  file  concurrently,  i.e.,  at  the  same  time?Clearly  write  your observations.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd1;
    char *buffer_parent = "helloparent";
    char *buffer_child = "hellochild";

    // Open the file for writing
    fd1 = open("f2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd1 == -1) {
        perror("Error opening file");
        return 1;
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred while forking
        perror("fork");
        return 1;
    } else if (pid > 0) {
        // Parent process
        printf("Parent process writing to file\n");

        // Write to the file using buffer_parent
        ssize_t wr = write(fd1, buffer_parent, strlen(buffer_parent));
        if (wr == -1) {
            perror("Error writing to file");
            return 1;
        }
    } else {
        // Child process
        printf("Child process writing to file\n");

        // Write to the file using buffer_child
        ssize_t wr = write(fd1, buffer_child, strlen(buffer_child));
        if (wr == -1) {
            perror("Error writing to file");
            return 1;
        }
         wait(NULL);
    }

    // Close the file descriptor
    close(fd1);

    // Wait for the child process to terminate
   

    printf("Both processes have written to the file\n");

    return 0;
}
