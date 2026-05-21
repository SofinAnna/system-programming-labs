// task_4_2.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd = open("numbers.bin", O_RDONLY);
    if (fd == -1) { perror("open"); return 1; }

    struct stat st;
    fstat(fd, &st);
    int count = st.st_size / sizeof(int);
    int *data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) { perror("mmap"); return 1; }

    int sum = 0;
    for (int i = 0; i < count; i++) sum += data[i];
    printf("Average: %.2f\n", (float)sum / count);

    munmap(data, st.st_size);
    close(fd);
    return 0;
}