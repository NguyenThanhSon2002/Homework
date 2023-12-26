#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void sig_handler1(int signum) {
    printf("I'm signal handler1\n");
    exit(EXIT_SUCCESS);
}

int main() {
    //time_t start, finish;
    sigset_t new_set, old_set;

    if (signal(SIGINT, sig_handler1) == SIG_ERR) {
        fprintf(stderr, "Cannot hadle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&new_set);
    sigemptyset(&old_set);

    sigaddset(&new_set, SIGINT);
    printf("new_set is %x\n", new_set);

    if (sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0) {
        if (sigismember(&new_set, SIGINT) == 1) {
            printf("SIGINT exist\n");
        } else if (sigismember(&old_set, SIGINT) == 0) {
            printf("SIGINT does not exist\n");
        }
    }

    while(1) {
        sleep(2);
    }

    return 0;
    
}