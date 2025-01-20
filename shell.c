#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define MAX 100
#define helper() printf("If you need Guide to use Viren's Shell type 'help'\n")

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

void accept_built_in_commands(char* args[]) {

    char *build_in_cmd[] = {"ls", "cd", "exit", "help"};

    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting Viren's Shell...\n");
        exit(0);
        return;
    } 

    bool found = false;
    for(int cmd = 0; cmd < 4; cmd++) {
        if(strcmp(args[0], build_in_cmd[cmd]) == 0) {
            found = true;
            break;
        }
    }

    if(!found) {
        printf("%s, is not supported Build-in Command\n", args[0]);
        return;
    }

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        return;
    }

    if(pid == 0) {
        printf("Child process executing the command\n");
        if(strcmp(args[0], "ls") == 0) {
            execvp("ls", args);
        } else if(strcmp(args[0], "cd") == 0) {
            if(chdir(args[1]) == -1) {
                perror("cd failed");
            }
        } else if(strcmp(args[0], "help") == 0) {
            show_help();
        }
        exit(0);
    } else {
        printf("Parent process waiting for child to complete\n");
        wait(NULL);
        printf("Child process completed\n");
    }
}

int main() {
    printf("Welcome to Viren's Shell\n");
    helper();
    while(1) {
        printf("~~> ");
        char command[MAX];
        char* args[MAX];
        fgets(command, MAX, stdin);
        parseInput(command, args);

        accept_built_in_commands(args);
    }
    return 0;
}