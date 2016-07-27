#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

#define ICMP   1

void pr_error(const char *msg);

int main(){
   int sfd, stat, on = 1;
   ssize_t smsg;
   struct sockaddr target;
   struct sockaddr_in *node;
   unsigned char *ptr;
   
   node = (struct sockaddr_in *)&target;

   node->sin_family = AF_INET;
   node->sin_port = 0;
   node->sin_addr.s_addr = inet_addr("192.168.0.1");

   sfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
   if (sfd == -1)
      pr_error("socket");
   
   stat = setsockopt(sfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
   if (stat == -1)
      pr_error("setsock");

   smsg = sendto(sfd, "HAI", 4, 0, &target, sizeof(struct sockaddr));
   if (smsg == -1)
      pr_error("sendto");
   return 0;
}

void pr_error(const char *msg){
   printf("%s: %m\n", msg);
   exit(EXIT_FAILURE);
}
