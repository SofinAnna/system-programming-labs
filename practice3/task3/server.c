#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    int client_fd = accept(server_fd, NULL, NULL);
    char filename[256];
    recv(client_fd, filename, sizeof(filename), 0);

    FILE *f = fopen(filename, "r");
    if (!f) {
        send(client_fd, "File not found", 14, 0);
    } else {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), f)) {
            send(client_fd, buffer, strlen(buffer), 0);
        }
        fclose(f);
    }
    close(client_fd);
    close(server_fd);
    return 0;
}