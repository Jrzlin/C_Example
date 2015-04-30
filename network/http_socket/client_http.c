#define _GNU_SOURCE
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>  
#include <string.h>
#include <netinet/tcp.h> 
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "base64.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"
/* printf color
  printf(KRED "red\n" RESET);
  printf(KGRN "green\n" RESET);
  printf(KYEL "yellow\n" RESET);
  printf(KBLU "blue\n" RESET);
  printf(KMAG "magenta\n" RESET);
  printf(KCYN "cyan\n" RESET);
*/
/*
 *  * Socket options
 *   */
#define SOCK_OPT_BROADCAST          0x01
#define SOCK_OPT_REUSEADDR          0x02
#define SOCK_OPT_NONBLOCK           0x04
#define SOCK_OPT_BLOCK              0x08
#define SOCK_OPT_NODELAY            0x10

int socket_set_fd_status (int fd, int non_block)
{
  int   flags;                          // file status

  flags = fcntl(fd, F_GETFL);
  if (flags < 0) {
    return(-1);
  }

  if (non_block) {
    flags |= O_NONBLOCK;
  } else {
    flags &= ~O_NONBLOCK;
  }
  if (fcntl(fd, F_SETFL, flags) < 0) {
    return(-1);
  }

  return(0);
}

int socket_set_options (int fd, uint32_t flags)
{
  int   on = 1;                         // enable option
  int   rc = 0;                         // return code

  /*
   * Set socket to non-blocking.
   */
  if (flags & (SOCK_OPT_NONBLOCK | SOCK_OPT_BLOCK)) {
    rc |= socket_set_fd_status(fd, (flags & SOCK_OPT_NONBLOCK));
  }

  /*
   * Allow broadcast option.
   */
  if (flags & SOCK_OPT_BROADCAST) {
    rc |= setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
  }

  /*
   * Allow reuse option.
   */
  if (flags & SOCK_OPT_REUSEADDR) {
    rc |= setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  }

  /*
   * Disable Nagle algorithm.
   */
  if (flags & SOCK_OPT_NODELAY) {
    rc |= setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &on, sizeof(on));
  }

  return(rc);
}

/*
 * Create TCP socket
 */
int socket_create_tcp_socket()
{
  int fd = -1;
  if((fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0){
    perror("[error]: can't create TCP socket\n");
    exit(1);
  }else{
    fprintf(stderr, "[action]: create a new socket[%d]\n",fd);
  }
  return fd;
}

/*
 * Authorization string for HTTP
 */
char *http_add_auth_header (char *buff, char *username, char *passwd)
{
  char      auth[strlen(username) + strlen(passwd) + 2];
  char      auth_enc[2 * (strlen(username) + strlen(passwd) + 1) + 1];
  ssize_t   len = sizeof(auth_enc);

  sprintf(auth, "%s:%s", username, passwd);
  base64_encode0(auth, strlen(auth), auth_enc, &len);
  sprintf(buff, "%s", auth_enc);
  return (buff);
}

int main(int argc, char **argv)
{
  struct sockaddr_in serv_addr;
  struct timeval timeout = { 10, 0 };
  int remote_fd = -1, rc = -1; 
  fd_set recv_fds;
  char *request_buff = NULL;
  char *auth_http = NULL;
  uint8_t *payload = NULL;

  if(argc < 3){
    fprintf(stderr,"[HELP] usage: ip web-content\n");
    fprintf(stderr,KYEL "       example: ./http_get 64.233.189.101 index.html user password\n" RESET);
    exit(1);
  }
  
  remote_fd = socket_create_tcp_socket();
  memset(&serv_addr, '0', sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(80);
  if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0){
    fprintf(stderr, "[error]: inet_pton error occured\n");
    exit(1);
  }

  if(connect(remote_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
    printf("[error]: connect to server failed %s\n",strerror(errno));
    if(errno != EINPROGRESS)
      exit(1);
  }

  //set socket non-blocking options
  socket_set_options(remote_fd,SOCK_OPT_NONBLOCK);

  //send http request message
  request_buff = malloc(1024);
  sprintf(request_buff,"GET /%s HTTP/1.1\r\n", argv[2]);
  if(argc > 3){
    auth_http = malloc(128);
    http_add_auth_header(auth_http, argv[3], argv[4]);
    sprintf(request_buff + strlen(request_buff) ,"Authorization: Basic %s\r\n",auth_http);
    free(auth_http);
    auth_http = NULL;
  }
  
  sprintf(request_buff + strlen(request_buff) , "Host: 127.0.0.1\r\n");
  sprintf(request_buff + strlen(request_buff),  "Connection: Keep-Alive\r\n\r\n");
  printf(KGRN"[DEBUG] : send request_buff \n %s \n"RESET, request_buff);
  
  rc = send(remote_fd, request_buff, strlen(request_buff),0);
  free(request_buff);
  request_buff = NULL;

  printf(KMAG "=======================================\n"RESET);
  
  while(remote_fd > 0){
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    FD_ZERO(&recv_fds);
    FD_SET(remote_fd, &recv_fds);

    rc = select( remote_fd + 1, &recv_fds, NULL, NULL, &timeout);
    if(rc < 0){
      if(errno != EINTR && errno != EAGAIN){
        fprintf(stderr, "select error: %s", strerror(errno));
        close(remote_fd);
        remote_fd = -1;
        continue;
      }
    }
    
    if(FD_ISSET(remote_fd, &recv_fds)){
      payload = malloc(1024*256);
      rc = read(remote_fd, payload, 1024*256);
      fprintf(stderr,RESET"received %d, data{\n" KRED "%s" RESET "\n}\n", rc, payload);
      free(payload);
      payload = NULL;
      break;
    }
  }

  close(remote_fd);
  remote_fd = -1;
  return 0;
}
