#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define QTD_MESSAGES 2
#define READ_PIPE 0
#define WRITE_PIPE 1

int main() {
    int pipeParent[2];
    int pipeChild[2];
    int returnStatus;
    char writeParent[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
    char writeChild[QTD_MESSAGES][20] = {"Sou o filho", "Filho na chuva"};
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeParent);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        return 1;
    }

    returnStatus = pipe(pipeChild);

    pid_t processId = fork();

    if (processId == 0) {
        srand(time(NULL));
        close(pipeParent[READ_PIPE]);
        close(pipeChild[WRITE_PIPE]);

        for (int i = 0; i < QTD_MESSAGES; i++) {
            printf("Writing from parent: Message %d is %s\n", i,
                   writeParent[i]);
            write(pipeParent[WRITE_PIPE], writeParent[i], sizeof(char) * 20);
            sleep(rand() % 20 / 10.0);
        }

        for (int i = 0; i < QTD_MESSAGES; i++) {
            read(pipeChild[READ_PIPE], readMessages, sizeof(char) * 20);
            printf("Reading from parent Message %d is %s\n", i, readMessages);
        }
    } else {
        close(pipeParent[WRITE_PIPE]);
        close(pipeChild[READ_PIPE]);

        for (int i = 0; i < QTD_MESSAGES; i++) {
            read(pipeParent[READ_PIPE], readMessages, sizeof(char) * 20);
            printf("Reading from child Message %d is %s\n", i, readMessages);
        }

        for (int i = 0; i < QTD_MESSAGES; i++) {
            printf("Writing from child: Message %d is %s\n", i, writeChild[i]);
            write(pipeChild[WRITE_PIPE], writeChild[i], sizeof(char) * 20);
            sleep(rand() % 20 / 10.0);
        }
    }

    wait(NULL);

    return 0;
}
