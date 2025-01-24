#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 100
#define Welcome() printf("Welcome to Viren's Shell\n");
#define Instruction() printf("If you need Guide to use Viren's Shell type 'help'\n")
#define Indicator() printf("~~> ");

void show_help() {
    printf("List of commands shell support\n");
    printf("1. ls                     - list all the files present at the current location\n");
    printf("2. cd <destination path>  - change current directory to provided destination directory\n");
    printf("3. exit                   - exit from the Viren's shell\n");
    printf("4. help                   - guide to use Viren's shell\n");
}

void format(char* str) {
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void parseInput(char* command, char* args[]) {
    
    char* token = strtok(command, " ");
    int i = 0;
    while(token != NULL) {
        format(token);
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    return;
}

void accept_io_redirection(char* args[]) {
    int start = 0;

    while (args[start] != NULL)
    {
        if(strcmp(args[start], ">") == 0) {
            args[start] = NULL;
            int fd = open(args[start + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd == -1) {
                perror("File open failed");
                break;
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;
        }

        if(strcmp(args[start], "<") == 0) {
            args[start] = NULL;
            int fd = open(args[start + 1], O_RDONLY);
            if(fd == -1) {
                perror("File open failed");
                break;
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;
        }
        start++;
    }
}

void run_command(char* args[]) {
    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if(pid == 0) {
        accept_io_redirection(args);
        execvp(args[0], args);
        perror("Exec failed");
        exit(1);
    } else {
        wait(NULL);
    }
}

bool accept_commands(char* args[]) {

    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting Viren's Shell...\n");
        exit(0);
    }

    if(strcmp(args[0], "cd") == 0) {
        if(chdir(args[1]) == -1) {
            perror("cd failed");
        }
        return true;
    }

    if(strcmp(args[0], "help") == 0) {
        show_help();
        return true;
    }

    run_command(args);
    return true;
}

int main() {
    Welcome();
    Instruction();
    while(1) {
        fflush(stdin);
        fflush(stdout);
        Indicator();
        char command[MAX];
        char* args[MAX];
        
        fgets(command, MAX, stdin);

        parseInput(command, args);
        accept_commands(args);
    }
    return 0;
}