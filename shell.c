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
    if (getline(&line, &buffsize, stdin) == -1) {
        if (feof(stdin)) { // if EOF or ctrl+D entered: quit
            exit(EXIT_SUCCESS);
        } else {
            perror("readline"); // if not then some weird error
            exit(EXIT_FAILURE);
        } // else
    } // if
    return line;
} //read_line

char **split_line(char *line) 
{
    int bufsize = 64; // 64 bytes
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if(!tokens) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line," \t\r\r\n\a"); // returns pointer to first token
    // is only not null if there is another token
    while(token != NULL) {
        tokens[position] = token; // sets token at tokens[i]
        position ++; // increase position
        if (position >= bufsize) { //no space for tokens in **tokens
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "realloc error\n");
                exit(EXIT_FAILURE);
            } // if
        } // if
        token = strtok(line," \t\r\r\n\a"); //points to next token
    } // while
    tokens[position] = NULL;
    return tokens;
} // split_line

int main(int argc, char *argv[]) 
{
    getDir();
    main_loop();
    return EXIT_SUCCESS;
} // main
