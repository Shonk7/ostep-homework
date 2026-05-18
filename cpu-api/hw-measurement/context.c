#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main() {
    // two processes have context switches
    // each process writes to one pipe and reads from another
    // parent writes to p1, child reads from p1 and writes to p2, parent reads from p2
    // this results in 2 context switches per iteration
    int p1[2], p2[2];
    pipe(p1); pipe(p2);
    int N = 100000;
    char buf = 'x';

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // child: read from p1, write to p2
        for (int i = 0; i < N; i++) {
            read(p1[0], &buf, 1);
            write(p2[1], &buf, 1);
        }
        return 0;
    }

    // parent: write to p1, read from p2
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++) {
        write(p1[1], &buf, 1);
        read(p2[0], &buf, 1);
    }
    gettimeofday(&end, NULL);

    wait(NULL);

    long ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec - start.tv_usec) * 1e3;
    // divide by 2*N because each loop = 2 context switches
    printf("Avg ctx switch cost: %.2f ns\n", (double)ns / (2 * N));
}
