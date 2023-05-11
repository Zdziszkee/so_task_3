//
// Created by Kacper Kuchta on 4/8/23.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Function for handling signals
void my_sig_handler(int signal) {
    printf("Captured signal with number: %d\n", signal);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        puts("Invalid number of arguments");
        exit(EXIT_FAILURE);
    }
    const int signalNumber = atoi(argv[1]);
    const int handleType = atoi(argv[2]);
    printf("process id: %d  ",getpid());
    // In case of SIGKILL or SIGSTOP
    if ((signalNumber == 9) || (signalNumber == 19)){
        perror("Can't handle SIGKILL or SIGSTOP");
        exit(EXIT_FAILURE);
    }
        switch (handleType) {
            case 1: {
                if (signal(signalNumber, SIG_DFL) == SIG_ERR) {
                    perror("SIGNAL ERROR");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 2: {
                if (signal(signalNumber, SIG_IGN) == SIG_ERR) {
                    perror("SIGNAL ERROR");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            case 3: {
                if (signal(signalNumber, my_sig_handler) == SIG_ERR) {
                    perror("SIGNAL ERROR");
                    exit(EXIT_FAILURE);
                }
                break;
            }
            default: {
                perror("Invalid handle type id");
                exit(EXIT_FAILURE);
            }
        }

    printf("Waiting for signal\n");
    pause();
    return 0;
}
