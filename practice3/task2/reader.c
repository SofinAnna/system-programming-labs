#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    mkfifo("myfifo", 0666);
    int fd = open("myfifo", O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }

    FILE *log = fopen("time.log", "w");
    char buffer[256];
    while (read(fd, buffer, sizeof(buffer)) > 0) {
        fputs(buffer, log);
        fflush(log);
    }
    fclose(log);
    close(fd);
    return 0;
}