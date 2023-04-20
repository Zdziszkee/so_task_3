//
// Created by Kacper Kuchta on 4/8/23.
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Wrong number of arguments were given!");
        exit(EXIT_FAILURE);
    }

    int handleType = atoi(argv[2]);
    int signal = atoi(argv[1]);
    pid_t id_p;
    switch (id_p = fork())
    {
        case -1:
            perror("Fork error");
            exit(-1);
        case 0:
            if (execl("c2.c", "a.c", signal, handleType, (char*)NULL) == -1)
            {
                perror("Execl error");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            sleep(1);
            break;
    }

    if(kill(id_p, signal) == -1)
        perror("Kill error");

}
