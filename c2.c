//
// Created by Kacper Kuchta on 4/19/23.
//



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Wrong number of arguments were given!");
        exit(EXIT_FAILURE);
    }
    int wait_status = 0;

    int handleType = atoi(argv[2]);
    int signal = atoi(argv[1]);

    for (int i = 0; i < 3; i++)
    {
        switch (fork())
        {
            case -1:
                perror("Fork error");
                exit(EXIT_FAILURE);
                break;
            case 0:
                if (execl("c2.c", "a.c", signal,handleType) == -1)
                {
                    perror("Execl error");
                    exit(EXIT_FAILURE);
                }
                break;
            default:
                break;
        }
    }

    wait(&wait_status);
    if (WIFSIGNALED(wait_status))
    {
        int wterm = WTERMSIG(wait_status);
        printf("Signal: %s", strsignal(wterm));
    }
    else
        printf("The process waited for all child processes to finish");

}