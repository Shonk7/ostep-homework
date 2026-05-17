#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
    int rc = fork();
    // re
    int fd = open("./in", O_RDWR , S_IRWXU);
    if (rc < 0) {
        perror("fork failed");
        exit(1);
    
    } else if (rc == 0) {
        printf("child\n");

        write(fd, "writen by child\n", strlen("writen by child\n"));
        // char buffer[1024];
        // int bytes = read(fd, buffer, sizeof(buffer) - 1);

        // if (bytes > 0) {
        //     buffer[bytes] = '\0'; // Null-terminate for printing
        //     printf("File Content:\n%s\n", buffer);
        // }
    } else {
        // parent needs to wait to make it determinisitic -> fork -> child (can do exec) -> parent
        wait(NULL);

        write(fd, "writen by parent\n", strlen("writen by parent\n"));
        printf("parent\n");

    }

    return 0;
}