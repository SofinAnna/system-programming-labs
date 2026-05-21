#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main() {
    mkfifo("myfifo", 0666);
    int fd = open("myfifo", O_WRONLY);
    if (fd == -1) { perror("open"); return 1; }

    for (int i = 0; i < 10; i++) {
        time_t t = time(NULL);
        char *time_str = ctime(&t);
        write(fd, time_str, strlen(time_str) + 1);
        sleep(1);
    }
    close(fd);
    return 0;
}