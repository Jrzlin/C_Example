#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
int main(int argc, char *argv[])
{
    int listenfd = -1, connfd = -1;
    struct sockaddr_in serv_addr; 
    struct timeval timeout = { 20, 0 };
    fd_set recv_fds;
    int rc = -1;
    char sendBuff[1025];
    char recvbuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        FD_ZERO(&recv_fds);
        FD_SET(listenfd, &recv_fds);
        if(connfd > 0)
         FD_SET(connfd, &recv_fds);

        rc = select(MAX(connfd, listenfd) + 1, &recv_fds, NULL, NULL, &timeout);
        printf("select rc %d\n",rc);
        if ( FD_ISSET(listenfd, &recv_fds) ) {
          connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
        }
        
        if ( FD_ISSET(connfd, &recv_fds) ) {
          rc = recv(connfd, recvbuff, sizeof(recvbuff), 0);
          printf("client rc %d\n",rc);
          if(rc < 0) break;
          ticks = time(NULL);
          snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
          write(connfd, sendBuff, strlen(sendBuff)); 
        }
        sleep(1);
     }
exit:
     close(connfd);
     close(listenfd);
     return 0;
}
