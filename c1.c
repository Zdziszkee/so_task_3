//
// Created by Kacper Kuchta on 4/8/23.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Wrong number of arguments were given!");
        exit(EXIT_FAILURE);
    }

    int handleType = atoi(argv[2]);
    int signalId = atoi(argv[1]);

    int child_PID = 0;
    int child_PGID = 0;
    int wait_status = 0;

    switch (child_PID = fork()) {
        case -1:
            perror("Fork error");
            exit(EXIT_FAILURE);
        case 0:
            setpgid(child_PID, 0);
            signal(signalId, SIG_IGN);
            if (execl("c2.c", "a.c", argv[2], signalId, handleType, (char *) NULL) == -1) {
                perror("Execl error");
                exit(EXIT_FAILURE);
            }

            break;
        default:
            sleep(1);
            child_PGID = getpgid(child_PID);
            if (kill(-child_PGID, 0) == -1) {
                perror("Child does not exist");
                exit(EXIT_FAILURE);
            }
            if (kill(-child_PGID, signalId) == -1) {
                perror("Kill error");
                exit(EXIT_FAILURE);
            }
            break;
    }

    sleep(1);

    wait(&wait_status);
    if (WIFSIGNALED(wait_status)) {
        int wterm = WTERMSIG(wait_status);
        printf("c2.c PID: %d \n", child_PID);
        printf("Signal: %s", strsignal(wterm));
    } else {
        printf("The process waited for all child processes to finish");
    }
}