#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>

void handle_heredoc(char *delimiter) {
    char *line;
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]);  // Close read end of the pipe
        while (1) {
            line = readline("> ");
            if (!line) {
                // Handle EOF (Ctrl+D)
                printf("Warning: here-document at line 1 delimited by end-of-file (wanted `%s`)\n", delimiter);
                exit(0);
            }
            if (strcmp(line, delimiter) == 0) {
                free(line);
                break;
            }
            write(pipefd[1], line, strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent process
        int status;
        close(pipefd[1]);  // Close write end of the pipe

        // Wait for the child to finish
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) {
            // Handle Ctrl+C in child
            printf("\nChild was terminated by Ctrl+C\n");
        } else {
            // Process the heredoc input from the pipe if needed
            char buffer[1024];
            int nbytes;
            while ((nbytes = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
                // Handle the input as needed
                write(STDOUT_FILENO, buffer, nbytes);
            }
        }
        close(pipefd[0]);
    }
}

int main() {
    char *delimiter = "END";

    printf("Starting heredoc. Enter lines, and type '%s' when finished:\n", delimiter);
    handle_heredoc(delimiter);

    return 0;
}
