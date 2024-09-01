#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum {
    HEREDOC_OFF,
    HEREDOC_ON,
    HEREDOC_INTERRUPTED
} t_heredoc_status;

t_heredoc_status manage_heredoc_status(int action) {
    static t_heredoc_status status = HEREDOC_OFF;

    if (action == HEREDOC_ON) {
        status = HEREDOC_ON;
    } else if (action == HEREDOC_INTERRUPTED) {
        status = HEREDOC_INTERRUPTED;
    } else if (action == HEREDOC_OFF) {
        status = HEREDOC_OFF;
    }

    return status;
}

void handle_sigint(int sig) {
    if (manage_heredoc_status(HEREDOC_ON) == HEREDOC_ON) {
        manage_heredoc_status(HEREDOC_INTERRUPTED);
        rl_replace_line("", 0);  // Clear the line
        rl_done = 1;  // Force readline to exit immediately
        write(STDOUT_FILENO, "\n", 1);  // Newline after Ctrl+C
    } else {
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);  // Clear the line
        rl_on_new_line();
        rl_redisplay();  // Redisplay the prompt
    }
}

void setup_signal_handling(void) {
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sa.sa_flags = SA_RESTART;  // Restart interrupted system calls
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

int heredoc(const char *delimiter) {
    char *line;

    manage_heredoc_status(HEREDOC_ON);  // Enter heredoc mode
    setup_signal_handling();  // Set up signal handling

    while (1) {
        line = readline("> ");
        if (manage_heredoc_status(HEREDOC_INTERRUPTED) == HEREDOC_INTERRUPTED) {
            printf("bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s`)\n", delimiter);
            free(line);
            manage_heredoc_status(HEREDOC_OFF);  // Exit heredoc mode
            return 1;
        }
        if (!line || strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        free(line);
    }

    manage_heredoc_status(HEREDOC_OFF);  // Exit heredoc mode
    return 0;
}

int main(void) {
    setup_signal_handling();  // Ensure signals are set up before entering the loop

    while (1) {
        char *rl = readline("minishell$ ");
        if (!rl) {
            printf("\nexit\n");
            break;
        }
        if (strcmp(rl, "heredoc") == 0) {
            heredoc("EOF");
        }
        free(rl);
    }
    return 0;
}

