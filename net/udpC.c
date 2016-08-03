#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>

int main(){
   int sfd;
   struct sockaddr_in dest;

   dest.sin_family = AF_INET;
   dest.sin_port = htons(8585);
   dest.sin_addr.s_addr = inet_addr("192.168.56.1");

   sfd = socket(AF_INET, SOCK_DGRAM, 0);
   printf("socket %m\n");

   sendto(sfd, "HAI", 4, 0, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   printf("sendto %m\n");

   return 0;
}
