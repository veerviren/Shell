﻿# Viren's Shell

## Introduction
Viren's Shell is a simple shell implementation in C. It supports basic shell commands like `ls`, `cd`, `exit`, `help` and other system commands. It also supports I/O redirection using `<` and `>` operators.

## Features
1. List all the files present at the current location using `ls` command.
2. Change current directory to provided destination directory using `cd <destination path>` command.
3. Exit from the Viren's shell using `exit` command.
4. Guide to use Viren's shell using `help` command.
5. I/O redirection using `<` and `>` operators.
6. Supports other system commands.
7. Error handling for invalid commands.

## How to use?
1. Clone the repository using `git clone`
2. Navigate to the project directory using `cd Virens-Shell`
3. Compile the code using `gcc shell.c -o shell`
4. Run the shell using `./shell`
5. Use the shell commands to interact with the shell.
6. Use `ls` command to list all the files present at the current location.
7. Use `cd <destination path>` command to change current directory to provided destination directory.
8. Use `exit` command to exit from the Viren's shell.

## Example
```
Welcome to Viren's Shell
If you need Guide to use Viren's Shell type 'help'
~~> ls
shell  shell.c
~~> cd ..
~~> ls
Virens-Shell
~~> exit
Exiting Viren's Shell...
```

## pstree screenshot
![pstree](./pstree.png)
<br>
In the above screenshot, the shell is running as a child process(ls) of the shell.
