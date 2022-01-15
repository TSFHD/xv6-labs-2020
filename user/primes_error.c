#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[]) {
    int p[2], prime, num, status;
    int p2[2];

    pipe(p);
    if (fork() == 0) {
        while (fork() == 0) {
            // printf("child %d %d\n", p[0], p[1]);
            pipe(p2);
            close(p[1]);
            if (read(p[0], &prime, 4) == 0) {
                close(p[0]);
                close(p[1]);
                break;
            }
            printf("prime %d\n", prime);
            while (read(p[0], &num, 4) != 0) {
                if (num % prime != 0) {
                    write(p2[1], &num, 4);
                    // printf("pipe: %d\n", num); 
                }
            }
            close(p[0]);
            // dup(p2[0]);
            p[0] = p2[0];
            p[1] = p2[1];
        }
        exit(status);
    } else {
        // printf("parent %d %d\n", p[0], p[1]);
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, 4);
        }
        close(p[1]);
        close(p[0]);
        wait(&status);
    }
    exit(0);
}