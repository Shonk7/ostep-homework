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
        printf("hello\n");
        // execle("/bin/ls", "ls", "-l", (char *)NULL);
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);

    } else {
        // parent needs to wait to make it determinisitic -> fork -> child (can do exec) -> parent
        wait(NULL);
        printf("goodbye\n");

    }

    return 0;
}