#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#define MAX 256

#define HELLO_PORT 12345
#define HELLO_GROUP "225.0.0.37"

main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    int cnt;
    char message[MAX];

    fgets(message, MAX, stdin);

    int sockfd = socket(AF_INET,SOCK_DGRAM,0);

    if (sockfd < 0){
      perror(" Failed to create a socket: ");
      return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));     //initialise structure to 0

    //Fill the structure 
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
    servaddr.sin_port=htons(HELLO_PORT);
     
    /* now just sendto() our destination */
    while (1) {
      if (sendto(sockfd, message, sizeof(message),0,(struct sockaddr *) &servaddr,
          sizeof(servaddr)) < 0) {
          
          perror("Error in sending: ");
          return 0;
      }
      
    }

    return 0;
}