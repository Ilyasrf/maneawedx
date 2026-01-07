#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int    picoshell(char **cmds[]) {
    int fd[2];
    int pid;
    int prev_fd = -1;
    int i = 0;
    
    while (cmds[i]) {
        if (cmds[i + 1] && pipe(fd) == -1)
            return 1;
        pid = fork();
        if (pid == -1)
            return 1;
        if (!pid) {
            if (prev_fd != -1) {
                dup2(prev_fd, 0);
                close(prev_fd);
            }
            if (cmds[i + 1]) {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit (1);
        }
        if (prev_fd != -1)
            close(prev_fd);
        if (cmds[i + 1]) {
            close(fd[1]);
            prev_fd = fd[0];
        }
        i++;
    }
    int status;
    while (wait(&status) > 0) ;
    return 0;
}