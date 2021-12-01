#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

// prints dir
/**
 * @brief prints the current directory
 * 
 */
void getDir() 
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("1730sh:%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
} // getDir

/**
 * @brief  main loop needs to do three things
 * 1) Read the command from STDIN, 2) separate command string
 * into a program and arguments, and 3) execute parseed commands
 */
void main_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        //printf(">");
        getDir();
        line = read_line();
        args = split_line(line);
        status = execute(args); 
        // status determines how long the loop executes

        free(line);
        free (args);
    } while(status);
} // main_loop

char *read_line(void)
{
    char *line = NULL; // holds the entered line
    ssize_t buffsize = 0; //getline will allocate buffersize
    if(getline(&line, &buffsize, stdin)) !=-1) {
        if (feof(stdin)) { // if EOF or ctrl+D enteterd: quit
            exit(EXIT_SUCCESS);
        } else {
            perror("readline"); // if not then some weird error
            exit(EXIT_FAILURE);
        } // else
    } // if
    return line;
} //read_line

int main(int argc, char *argv[]) 
{
    getDir();
    main_loop();
    return EXIT_SUCCESS;
} // main
