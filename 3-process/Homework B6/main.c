#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    int status;
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == 0) {
        //Process con
        printf("\nI'm child process. \nmy PID: %d.\nMy parent PID: %d\n", getpid(), getppid());
        printf("\nChild process terminate after 7 seconds\n");
        sleep(2);
    } else {
        //Process cha
        waitpid(child_pid, &status, 0);

        printf("\nIm the parent process, my PID: %d\n", getpid());

        if(WIFEXITED(status)){
            printf("Normally termination, status = %d\n", WEXITSTATUS(status));
        }else if(WIFEXITED(status)){
            printf("Abnormally termination, signal value = %d\n", WTERMSIG(status));
        }
    }
    
    return 0;
}