#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int counter = 0;

void sig_handler1(int num)
{
    printf("\nI'm SIGINT: %d, counter: %d\n", num, counter++);
}

void sig_handler2(int num)
{
    printf("\nI'm Son, i create SIGUSR1: %d\n", num);
}

void sig_handler3(int num)
{
    printf("\nI'm Sondz, i create SIGUSR1: %d\n", num);
}

int main()
{
    if (signal(SIGINT, sig_handler1) == SIG_ERR) {
        fprintf(stderr, "Cannot hadle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1,sig_handler2);
    signal(SIGUSR2,sig_handler2);

    while(1) {
        sleep(2);
    }

    return 0;
}