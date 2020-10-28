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
    int p = 0;
    while (1) {
        bzero(buffer, sizeof(buffer));
        printf("Enter the message: ");
        p = 0;
        while ((buffer[p++] = getchar()) != '\n');
        write(sockfd, buffer, sizeof(buffer));
        bzero(buffer, sizeof(buffer));
        read(sockfd, buffer, sizeof(buffer));
        printf("\nReceived from server: %s\n", buffer);
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client exiting...");
            break;
        }
    }
}

int main(int argc, char** argv) {
    int sockfd, connfd;
    struct sockaddr_in servaddr;
  
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("Socket creation failed!!!\n");
        exit(0);
    } else {
        printf("Socket successfully created...\n");
    }

    bzero(&servaddr, sizeof(servaddr)); 
  
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    servaddr.sin_port = htons(PORT); 
  
    if (connect(sockfd, (struct sockaddr*)& servaddr, sizeof(servaddr)) != 0) { 
        printf("Connection with the server failed!!!\n"); 
        exit(0); 
    } 
    else {
        printf("Connected to the server...\n");
    }

    pleaseChat(sockfd); 
  
    close(sockfd); 
} 