/*
 *  showip.c
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//int getaddrinfo(const char* node, const char* service, const struct addrinfo *hints, struct addrinfo **res)
int main(int argc, char *argv[])
{
  int status;
  struct addrinfo hints, *res, *p;
  char ipstr[INET6_ADDRSTRLEN];

  if(argc != 2){
    fprintf(stderr,"usage: showip hostname\n");
    return 1;
  }
  
  memset(&hints,0,sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  
  if( (status = getaddrinfo(argv[1], "3490", &hints, &res)) !=0 ){
    fprintf(stderr, "getaddrinfo error:%s\n", gai_strerror(status));
    return 2;
  }

  printf("IP Addresses for %s:\n\n",argv[1]);
  for(p=res ; p!=NULL ; p = p->ai_next)
  {
    void *addr;
    char *ipver;
    if(p->ai_family == AF_INET){
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";
    }else{
        struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = "IPv6";
    }

    //convert the IP to string and printf it.
    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
    printf(" %s:%s\n", ipver, ipstr);
  }
    
  freeaddrinfo(res);
  return 0;
  
}
