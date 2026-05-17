#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
    int rc = fork();

    if (rc < 0) {
        perror("fork failed");
        exit(1);

    } else if (rc == 0) {
        printf("hello, pid = %d\n", (int) getpid());

    } else {
        int w = waitpid(rc, NULL, 0);
        printf("goodbye pid = %d, waitpid returned = %d\n", (int) getpid(), w);

    }

    return 0;
}
