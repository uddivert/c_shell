#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

void getDir() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("1730sh:%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
} // getDir

int main(int argc, char *argv[]) 
{
    getDir();
    return EXIT_SUCCESS;
} // main
