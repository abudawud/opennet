#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

struct iphdr {
   uint8_t 
      ihl:4,
      ver:4,
      tos;
   uint16_t
      tlen,
      id,
      flag;
   uint8_t
      ttl,
      proto;
   uint16_t chksum;
   unsigned int 
      srcAddr,
      dstAddr;
};

struct icmphdr {
   uint16_t
      type:8,
      code:8,
      chksum;
};

void printe(const char *msg);

int main(){
   struct iphdr ip;
   struct icmphdr icmp;
   struct sockaddr_in dest;
   int sock;
   ssize_t stat;
   uint8_t * packet;
   register unsigned int i;
   void * tmp;

   packet = (uint8_t *)&ip;
   tmp = (uint8_t *)packet;
   
   memset(&dest, 0, sizeof(struct sockaddr_in));
   memset(&ip, 0, sizeof(struct iphdr));
   
   ip.ver = 4;
   ip.ihl = 5;
   ip.tos = 7;
   ip.tlen = htons(20);
   ip.id = htons(0);
   ip.flag = 0;
   ip.ttl = 255;
   ip.proto = 1;
   ip.chksum = 0;
   ip.srcAddr = inet_addr("192.168.0.100");
   ip.dstAddr = inet_addr("192.168.0.102");
   
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = ip.dstAddr;

   for(i = 0; i < 20; i++)
      printf("%d.", *((uint8_t *)tmp++));
   printf("\n");

   sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
   if (sock == -1)
      printe("socket");

#ifndef IP_HDRINCL
   printe("raw");
#endif
   stat = sendto(sock, &ip, sizeof(struct iphdr), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   if (stat == -1)
      printe("send");

   puts("SUCCESS");
   
   

   return 0;
}

void printe(const char *msg){
   printf("%s: %m\n", msg);
   exit(EXIT_FAILURE);
}
