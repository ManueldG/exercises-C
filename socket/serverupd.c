 // server program for udp connection
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include <time.h>

#define PORT 5000
#define MAXLINE 1000


// Driver code
int main()
{
    time_t t = 0;
    t = time(&t);      
//    int var = atoi("123");
    printf("\ninizio %s \n",ctime(&t));
    char buffer[100];
    char *message = "Hello Client";
    int listenfd;
    unsigned int len;
    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));
    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);        

    //htons (host to network short) littleendian -> bigendian               
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //host to network long
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET; 
 
    // bind server address to socket descriptor
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
     
    //receive the datagram


    len = sizeof(cliaddr);
    // n < 0 errore - n = 0 datagram vuoto - n > 0 ok
    int n;
    for(int i = 0 ; i < 1000000 ; i++ ){    
    n = recvfrom(listenfd, buffer, sizeof(buffer),
            0, (struct sockaddr*)&cliaddr,&len); //receive message from server
    buffer[n] = '\0';
    if( n >= 0 ){ 
       printf("%u",cliaddr.sin_addr.s_addr);
       puts("rec:");   
       puts(buffer);
    }
    else
       printf("\nerrore msg\n");     
    // send the response
    struct tm *t_st;
    char *s;
    s = calloc(sizeof(char), strlen(message) + 10);

    t = time(&t);
    t_st = localtime(&t);
    sprintf(s,"\n%s %d:%d:%d \n",message,t_st->tm_hour,t_st->tm_min,t_st->tm_sec);
    sendto(listenfd, s, strlen(s) + 1, 0, (struct sockaddr*)&cliaddr,sizeof(cliaddr)); 
    }
}