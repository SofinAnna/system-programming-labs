// task_3_1.c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

void report(const char *msg) {
    perror(msg);
    _exit(1);
}

int main() {
    int fd[2];
    if (pipe(fd) == -1) report("pipe failed");

    pid_t pid = fork();
    if (pid == -1) report("fork failed");

    if (pid == 0) { // child
        close(fd[1]);
        char buffer[256];
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n == -1) report("child read failed");
        buffer[n] = '\0';

        for (int i = 0; buffer[i]; i++) {
            if (islower(buffer[i]))
                buffer[i] = toupper(buffer[i]);
        }
        printf("Child received & converted: %s\n", buffer);
        close(fd[0]);
    } else { // parent
        close(fd[0]);
        char input[256];
        printf("Enter string: ");
        fflush(stdout);
        if (!fgets(input, sizeof(input), stdin)) report("fgets failed");
        if (write(fd[1], input, strlen(input) + 1) == -1) report("parent write failed");
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}