//
// Created by Kacper Kuchta on 4/19/23.
//

#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500
#define _GNU_SOURCE


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments were given!");
        exit(EXIT_FAILURE);
    }
    int wait_status = 0;

    int handleType = atoi(argv[2]);
    int signalNumber = atoi(argv[1]);

    if (signal(signalNumber, SIG_IGN) == SIG_ERR) {
                    perror("SIGNAL ERROR");
                    exit(EXIT_FAILURE);

                }
    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
            case -1:
                perror("Fork error");
                exit(EXIT_FAILURE);
                break;
            case 0:
                if (execlp("./a.x", "./a.x", argv[1],argv[2],(char*)NULL) == -1)
                {
                    perror("Execl error");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < 3; i++)
    {
    wait(&wait_status);
        if (WIFSIGNALED(wait_status))
    {
        int wterm = WTERMSIG(wait_status);
        printf("Signal: %s", strsignal(wterm));
    }
    else
        printf("The process waited for all child processes to finish");
    }


}