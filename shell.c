#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define helper() printf("If you need Guide to use Viren's Shell type 'help'\n")
void show_help() {
    printf("List of commands shell support\n");
    printf("1. ls\n");
    printf("2. cd\n");
    printf("3. exit\n");
    printf("4. help\n");
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

    if(strcmp(args[0], "ls") == 0) {
        printf("ls command\n");
    } else if(strcmp(args[0], "cd") == 0) {
        printf("cd command\n");
    }
    else if(strcmp(args[0], "exit") == 0) {
        printf("Exiting the shell...\n");
        exit(0);
    }
    else if(strcmp(args[0], "help") == 0) {
        show_help();
    }else {
        printf("Build-in Command not found\n");
    }
}

int main() {
    helper();
    while(1) {
        printf("~~> ");
        char command[MAX];
        char* args[MAX];
        fgets(command, MAX, stdin);
        parseInput(command, args);

        int st = 0;
        // while(args[st] != NULL) {
        //     printf("%s\n", args[st]);
        //     st++;
        // }

        accept_built_in_commands(args);
    }
    return 0;
}