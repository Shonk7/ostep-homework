#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(void) {
    // create pipe
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe failed");
        exit(1);
    }

    // first child process
    int c1 = fork();
    if (c1 < 0) {
        perror("fork c1 failed");
        exit(1);
    }
    if (c1 == 0) {
        // close rreading end of pipe (stdin) + write to writing end of pipe (stdout) before closing
        // close(pipefd[0]);
        const char *msg = "hello from child1 via pipe";
        write(pipefd[1], msg, strlen(msg));
        // close(pipefd[1]);
        exit(0);
    }

    // second child process (reader)
    int c2 = fork();
    if (c2 < 0) {
        perror("fork c2 failed");
        exit(1);
    }
    if (c2 == 0) {
        // close(pipefd[1]);
        // read into buffer
        char buf[128];
        int n = read(pipefd[0], buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("child2 received: %s\n", buf);
        }
        // close(pipefd[0]);
        exit(0);
    }

    // back to parent
    // close(pipefd[0]);
    // close(pipefd[1]);

    int w1 = waitpid(c1, NULL, 0);
    int w2 = waitpid(c2, NULL, 0);
    printf("parent pid=%d waited for %d and %d\n", (int)getpid(), w1, w2);

    return 0;
}