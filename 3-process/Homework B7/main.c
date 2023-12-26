#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void signal_handler(int signum)
{
    printf("\nI'm signal_handler\n");
    wait(NULL);
}

int main(int argc, const char argv[])
{
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0) {
        printf("\nI'm children process\n");
    } else {
        signal(SIGCHLD,signal_handler);
        printf("\nI'm parent process\n");
        while(1);
    }
}