#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    int fd = open("/dev/zero", O_RDONLY);
    char buf[1];
    int N = 100000;

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < N; i++) {
        read(fd, buf, 0);
    }
    gettimeofday(&end, NULL);

    long ns = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_usec - start.tv_usec) * 1e3;
    printf("Avg syscall cost: %.2f ns\n", (double)ns / N);
    close(fd);
}
