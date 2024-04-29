#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_FILE "myfifo"

int count_vowels(char *sentence) {
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == 'a' || sentence[i] == 'e' || sentence[i] == 'i' || sentence[i] == 'o' || sentence[i] == 'u' ||
            sentence[i] == 'A' || sentence[i] == 'E' || sentence[i] == 'I' || sentence[i] == 'O' || sentence[i] == 'U') {
            count++;
        }
    }
    return count;
}

int main() {
    int fd;
    pid_t pid;
    char sentence[100];

    // Create named pipe
    mkfifo(FIFO_FILE, 0666);

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process: Waiting for data...\n");
        fd = open(FIFO_FILE, O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        // Read sentence from the pipe
        read(fd, sentence, sizeof(sentence));
        close(fd);

        // Count vowels
        int vowels = count_vowels(sentence);

        // Print sentence and number of vowels
        printf("Child process: Read %s, number of vowels = %d\n", sentence, vowels);
    } else {
        // Parent process
        printf("Parent process: Please enter a sentence: ");
        fgets(sentence, sizeof(sentence), stdin);

        // Open pipe for writing
        fd = open(FIFO_FILE, O_WRONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Write sentence to pipe
        write(fd, sentence, strlen(sentence) + 1);
        close(fd);
    }

    return 0;
}
