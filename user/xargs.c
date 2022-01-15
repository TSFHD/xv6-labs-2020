#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define BUFFER_SIZE 512

int
main(int argc, char *argv[]) {
    char *args[MAXARG], buf[BUFFER_SIZE], *p, *arg;
    int arg_cnt, read_cnt, xargs_start;
    
    arg_cnt = 0;
    read_cnt = 0;
    args[arg_cnt++] = argv[1];
    for (int i = 2; i < argc; i++) {
        args[arg_cnt++] = argv[i];
    }
    xargs_start = arg_cnt;
    

    while (read(0, &buf[read_cnt], 1) != 0) {
        read_cnt++;
        if (buf[read_cnt - 1] == '\n') {
            buf[read_cnt - 1] = ' ';
            p = buf; 
            arg = p;           
            while (*p++) {
                
                if (*p == ' ') {
                    *p = 0;
                    args[arg_cnt++] = arg;
                    // strcpy(args[arg_cnt++], arg);
                    p++;
                    arg = p;
                }
            }
            args[arg_cnt] = 0;
            arg_cnt = xargs_start;
            read_cnt = 0;
            if (fork() == 0) {
                exec(args[0], args);
            } else {
                wait(0);
            }
        }
    }
    exit(0);
}