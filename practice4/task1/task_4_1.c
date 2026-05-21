// task_4_1.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char **lines = NULL;
    int count = 0;
    char buffer[256];

    printf("Enter strings (empty line to stop):\n");
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        if (strlen(buffer) == 0) break;

        lines = realloc(lines, (count + 1) * sizeof(char*));
        lines[count] = malloc(strlen(buffer) + 1);
        strcpy(lines[count], buffer);
        count++;
    }

    printf("\nReverse order:\n");
    for (int i = count - 1; i >= 0; i--) {
        printf("%s\n", lines[i]);
        free(lines[i]);
    }
    free(lines);
    return 0;
}