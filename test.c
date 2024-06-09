#include <stdio.h>

int open_quotes(char *string) {
    int i = 0;
    int inside_single_quotes = 0;
    int inside_double_quotes = 0;

    while (string[i] != '\0') {
        if (string[i] == '"' && !inside_single_quotes)
            inside_double_quotes = !inside_double_quotes;
        else if (string[i] == '\'' && !inside_double_quotes)
            inside_single_quotes = !inside_single_quotes;

        if (string[i] == '\'' && !inside_single_quotes && !inside_double_quotes)
            return 1;
        else if (string[i] == '"' && !inside_double_quotes && !inside_single_quotes)
            return 1;

        i++;
    }

    return 0;
}

int main() {
    char *str1 = "echo \"Hello, World!\"";
    char *str2 = "echo \"She said, 'Hello!'\"";
    char *str3 = "echo 'Hello, World!'";

    printf("%d\n", open_quotes(str1)); // Output: 1
    printf("%d\n", open_quotes(str2)); // Output: 1
    printf("%d\n", open_quotes(str3)); // Output: 0

    return 0;
}
