#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int my_popen(const char *file, char *const argv[], char type) {
    if (!file || !argv || (type != 'r' && type != 'w')) {
        errno = EINVAL;
        return -1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return -1; // Failed to create the pipe
    }

    pid_t pid = fork();
    if (pid == -1) {
        // Fork failed
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }

    if (pid == 0) {
        // Child process
        if (type == 'r') {
            close(pipefd[0]); // Close unused read end
            if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(pipefd[1]);
        } else if (type == 'w') {
            close(pipefd[1]); // Close unused write end
            if (dup2(pipefd[0], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(pipefd[0]);
        }

        // Execute the command
        execvp(file, argv);

        // If execvp fails, exit with error
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    if (type == 'r') {
        close(pipefd[1]); // Close unused write end
        return pipefd[0]; // Return read end
    } else if (type == 'w') {
        close(pipefd[0]); // Close unused read end
        return pipefd[1]; // Return write end
    }

    // Should not reach here
    return -1;
}

int main() {
    char *args[] = {"ls", "-l", NULL};
    int fd = my_popen("ls", args, 'r');
    if (fd == -1) {
        perror("my_popen");
        return 1;
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
    }

    close(fd);
    return 0;
}
