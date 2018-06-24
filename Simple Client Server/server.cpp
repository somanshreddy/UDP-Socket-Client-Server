#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <vector>
#define MAX 255

using namespace std;


int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Port number not provided. \n");
        return 0;
    }

    struct sockaddr_in servaddr, cliaddr;
    int port_no = atoi(argv[1]);
    char buffer[MAX];                                       //holds the string received from client
    char str[MAX];                                          //holds the string to be sent to the client

    // Get a socket file descriptor
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);           

    if(sockfd < 0){                                         //returns non negative integer if successful
        perror("Failed to create a socket");
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));                 // initialize both to 0
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family    = AF_INET;                       // IPv4
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port_no);


    // Bind the socket to the protocol address (IP + port number) 
    if(bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){
        perror("Bind failed");
        return 0;
    }

    int n;
    socklen_t len = 20;

    while(1){
        
        n = recvfrom(sockfd, (char *)buffer, MAX, 
                0, (struct sockaddr *) &cliaddr,          //cliaddr stores the address of the client which sent data to the server
            &len);                                                  // which is used in the sendto() function to identify which client data must be sent to

        buffer[n] = '\0';

        printf("Client : %s\n", buffer);

        fgets(str, MAX, stdin);
    
        sendto(sockfd, (const char *)str, strlen(str), 
        0, (const struct sockaddr *) &cliaddr,
            len);

    }

    close(sockfd);
    
    return 0;
}