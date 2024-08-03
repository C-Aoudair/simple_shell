#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * The main function of simple shlell program
 * 
 * @return 0
 */
int main(int argc, char *argv[], char *envp[]) {
    char *line = NULL;
    int *status;
    size_t len = 0;
    ssize_t read;
    while (1) {
        printf("simple-shell> ");
        read = getline(&line, &len, stdin);
        if (read == -1) {
            break;
        }
        line[read - 1] = '\0';
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            execve(line, argv, envp);
            perror("simple-shell");
            exit(0);
        }
        wait(status);    
    }
    free(line);
    return 0;
    
}