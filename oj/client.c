#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/type.h>
int main(int argc, char const *argv[])
{
    char *msg="Hello,this is udp.";
    int sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sock==INVALID_SOCKET){
        printf("Error\n");
        return -1;
    }
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family=AF_INET;
    address.sin_addr.S_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(6201);
    sendto(sock,msg,strlen(msg),0,(struct sockaddr *)&address,sizeof(address));
    close(sock);
    return 0;
}
