#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    if(argc == 1) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }
    printf("Summing up the numbers...\n");
    int sum = 0;
    for(int i = 1; i < argc; i++) {
        sum += atoi(argv[i]);
    }

    printf("Sum: %d\n", sum);
    return 0;
}