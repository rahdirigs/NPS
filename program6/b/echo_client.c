#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

#define PORT 8000
#define MAXSZ 100

int main(int argc, char** argv) {
    int sockfd;

    struct sockaddr_in serverAddress;

    int n;
    char msg1[MAXSZ];
    char msg2[MAXSZ];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddress.sin_port = htons(PORT);

    connect(sockfd,(struct sockaddr *)& serverAddress, sizeof(serverAddress));

    while(1) {
        printf("\nEnter the message to be sent:\n");
        fgets(msg1, MAXSZ, stdin);

        if(msg1[0] == '#')
            break;

        n = strlen(msg1) + 1;
        send(sockfd, msg1, n, 0);

        n = recv(sockfd, msg2, MAXSZ, 0);
    }

    return 0;
}