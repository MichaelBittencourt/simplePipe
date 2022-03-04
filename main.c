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
    int pipeFileDescriptors[2];
    int returnStatus;
    char writeMessages[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeFileDescriptors);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        return 1;
    }

    pid_t processId = fork();

    if (processId == 0) {
        srand(time(NULL));
        close(pipeFileDescriptors[READ_PIPE]);

        for (int i = 0; i < QTD_MESSAGES; i++) {
            printf("Writing Message %d is %s\n", i, writeMessages[i]);
            write(pipeFileDescriptors[WRITE_PIPE], writeMessages[i],
                  sizeof(char) * 20);
            sleep(rand() % 20 / 10.0);
        }
    } else {
        close(pipeFileDescriptors[WRITE_PIPE]);

        for (int i = 0; i < QTD_MESSAGES; i++) {
            read(pipeFileDescriptors[READ_PIPE], readMessages,
                 sizeof(char) * 20);
            printf("Reading Message %d is %s\n", i, readMessages);
        }
    }

    wait(NULL);

    return 0;
}
