// task_4_3.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>

void sighup_handler(int sig) {
    FILE *conf = fopen("config.txt", "r");
    if (conf) {
        char line[256];
        if (fgets(line, sizeof(line), conf))
            printf("Daemon reloaded config: %s\n", line);
        fclose(conf);
    } else {
        printf("Daemon: config.txt not found\n");
    }
}

int main() {
    pid_t pid = fork();
    if (pid < 0) exit(1);
    if (pid > 0) exit(0);

    setsid();
    chdir("/");
    umask(0);
    for (int i = 0; i < 3; i++) close(i);

    signal(SIGHUP, sighup_handler);

    while (1) {
        pause();
    }
    return 0;
}