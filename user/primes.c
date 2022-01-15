#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void child_process(int p[]);

int
main() {
    int p[2];

    pipe(p);
    if (fork() == 0) {
        close(p[1]);
        child_process(p);
    } else {
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        close(p[0]);
        wait(0);
    }
    exit(0);
}

void child_process(int p[]) {
    int prime, num, pp[2];

    if (read(p[0], &prime, sizeof(int)) == 0) {
        close(p[0]);
        exit(0);
    }
    printf("prime %d\n", prime);
    pipe(pp);
    if (fork() == 0) {
        close(pp[1]);
        child_process(pp);
    } else {
        
        while (read(p[0], &num, sizeof(int)) != 0) {
            if (num % prime != 0) {
                write(pp[1], &num, sizeof(int));
            }
        }
    }
    exit(0);
}