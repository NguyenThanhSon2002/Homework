#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid = fork();

    if(child_pid == 0){
        printf("\nI'm child process. \nmy PID: %d.\nMy parent PID: %d\n", getpid(), getppid());
        while(1);
    }else{
        printf("I'm parent process.");
        while(1);
    }

    return 0;

}
