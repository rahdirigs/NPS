#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

#define MAX_SIZE 80
#define PORT 6970

void pleaseChat(int sockfd) {
    char buffer[MAX_SIZE];
    int p;
    while (1) {
        bzero(buffer, MAX_SIZE);
        read(sockfd, buffer, sizeof(buffer));
        printf("Received from client : %s\n", buffer);
        printf("To client: ");
        bzero(buffer, MAX_SIZE);
        p = 0;
        while ((buffer[p++] = getchar()) != '\n');
        write(sockfd, buffer, sizeof(buffer));

        if (strncmp("exit", buffer, 4) == 0) {
            printf("Server chose to Exit...\n");
            break;
        }
    }
}

int main() {
    struct sockaddr_in servaddr, cliaddr;
    int sockfd, connfd, len;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Creation of socket failed!!!");
        exit(0);
    } else {
        printf("Created socket successfully...\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (struct sockaddr_in*)& servaddr, sizeof(servaddr))) != 0) {
        printf("Binding to socket failed!!!");
        exit(0);
    } else {
        printf("Socket successfully bound...\n");
    }

    if (listen(sockfd, 5) != 0) {
        printf("Listening failed!!!\n");
        exit(0);
    } else {
        printf("Server listening...\n");
    }

    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr*)& cliaddr, &len);

    if (connfd < 0) {
        printf("Server accept failed!!!");
        exit(0);
    } else {
        printf("Server has accepted the client...\n");
    }

    pleaseChat(connfd);

    close(sockfd);
}