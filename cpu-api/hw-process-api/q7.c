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
        close(STDOUT_FILENO);
        printf("hello, pid = %d", (int) getpid());
    } else {
        int w = wait(NULL);
        printf("goodbye wait = %d, pid = %d\n", w, (int) getpid());

    }

    return 0;
}