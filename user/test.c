#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
//   char *argv[3];

//   argv[0] = "echo";
//   argv[1] = "hello";
//   argv[2] = 0;
//   exec("echo", argv);
//   printf("exec error\n");
//   exit(0);

    char *dest[2], *str;
    dest[0] = " ";
    dest[1] = " ";
    
    str = "abc";
    strcpy(dest[0], str);
    printf("%s\n", dest[0]);
    str = "def";
    printf("%s\n", dest[0]);
    strcpy(dest[1], str);
    printf("%s\n", dest[0]);
    printf("%s\n", dest[1]);
    exit(0);
}