#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), inet_addr("127.0.0.1")};
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    char filename[256];
    printf("Enter filename: ");
    scanf("%s", filename);
    send(sock, filename, strlen(filename) + 1, 0);

    char buffer[4096];
    while (recv(sock, buffer, sizeof(buffer), 0) > 0) {
        printf("%s", buffer);
    }
    close(sock);
    return 0;
}