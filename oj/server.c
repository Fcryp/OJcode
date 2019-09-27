#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/type.h>
int main(int argc, char const *argv[])
{
    char buf[200];
    int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    struct sockaddr_in host;
    bzero(&host,sizeof(host));
    host.sin_family=AF_INET;
    host.sin_addr.s_addr=htonl(INADDR_ANY);
    host.sin_port=htons(6201);
    bind(sock,(struct sockaddr *)&host,sizeof(host));
    while(1){
        recvfrom(sock,buf,sizeof(buf),0);
        printf("Client:%s",buf);

    }

    return 0;
}
