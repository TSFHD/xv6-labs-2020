#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main() {
    int pid;
    int p[2];
    char buffer[4];

    pipe(p);
    pid = fork();
    if (pid == 0) {
        read(p[0], buffer, 4);
        printf("%d: received %s\n", getpid(), buffer);
        write(p[1], "pong", 4);
    } else {
        write(p[1], "ping", 4);
        wait(&pid);
        read(p[0], buffer, 4);
        printf("%d: received %s\n", getpid(), buffer);
    }
    exit(0);
}