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

bool accept_built_in_commands(char* args[]) {

    char *build_in_cmd[] = {"ls", "cd", "exit", "help"};

    bool found = false;
    for(int cmd = 0; cmd < 4; cmd++) {
        if(strcmp(args[0], build_in_cmd[cmd]) == 0) {
            found = true;
            break;
        }
    }

    if(!found) {
        printf("%s, is not supported Build-in Command\n", args[0]);
        return found;
    }

    if(strcmp(args[0], "exit") == 0) {
        printf("Exiting Viren's Shell...\n");
        exit(0);
    }

    if(strcmp(args[0], "cd") == 0) {
        if(chdir(args[1]) == -1) {
            perror("cd failed");
        }
        else {
            printf("Changing directory to %s\n", args[1]);
        }
        return found;
    }

    if(strcmp(args[0], "help") == 0) {
        show_help();
        return found;
    }

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if(pid == 0) {
        if(strcmp(args[0], "ls") == 0) {
            execvp("ls", args);
            perror("ls failed");
        }
        exit(1);
    } else {
        wait(NULL);
    }

    return found;
}

bool accept_custom_program_commands(char* args[]) {

    printf("Trying custom program execution commands..\n");
    
    int file_status = access(args[0], F_OK);
    if(file_status == -1) {
        printf("%s path not found\n", args[0]);
        return false;
    }

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if(pid == 0) {
        execvp(args[0], args);
        perror("Execution failed");
        exit(1);
    } else {
        wait(NULL);
    }

    return true;
}

bool accept_io_redirection(char* args[]) {
    return true;
}

int main() {
    printf("Welcome to Viren's Shell\n");
    helper();
    while(1) {
        // flush the previous input
        fflush(stdin);
        fflush(stdout);
        printf("~~> ");
        char command[MAX];
        char* args[MAX];
        fgets(command, MAX, stdin);
        parseInput(command, args);

        if(accept_built_in_commands(args)) {
            continue;
        }
        else if(accept_custom_program_commands(args)) {
            continue;
        }
        else if(accept_io_redirection(args))
        {
            continue;
        }
        else {
            printf("Sorry!! %s Command not supported by Viren's shell\n", args[0]);
        }
    }
    return 0;
}