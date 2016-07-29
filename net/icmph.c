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
   uint8_t
      type,
      code;
   uint16_t
      chksum,
      id,
      seq;
};

void printe(const char *msg);
uint16_t checksum(uint16_t * packet, int len);

int main(){
   struct iphdr *ip;
   struct icmphdr *icmp;
   struct sockaddr_in dest;
   int sock;
   ssize_t stat;
   uint8_t packet[40], * ptr;
   register unsigned int i;
   void * tmp;

//   ptr = packet;
   ip = (struct iphdr *)packet;
   icmp = (struct icmphdr *)&packet[20];
  // tmp = (uint8_t *)packet;
   
   memset(&dest, 0, sizeof(struct sockaddr_in));
   memset(ip, 0, sizeof(struct iphdr));
  
//   printf("%x\t%x\t%x\n", ptr, ip, packet);
//  puts("here"); 
   ip->ver = 4;
   ip->ihl = 5;
   ip->tos = 7;
   ip->tlen = 0x1800;
   ip->id = 0;
   ip->flag = 0;
   ip->ttl = 255;
   ip->proto = 1;
   ip->chksum = 0xc83b;
   ip->srcAddr = inet_addr("192.168.0.100");
   ip->dstAddr = inet_addr("192.168.0.102");
   
   printf("tos %x, %x\n", &ip->tos, &packet[1]);
//   printf("%X \n", packet[0]); 
   dest.sin_family = AF_INET;
   dest.sin_addr.s_addr = ip->dstAddr;

//  checksum((uint16_t *)ip, 20);
   
   icmp->type = 8;
   icmp->code = 0;
   icmp->chksum = 0xfff7;
   icmp->id = 0;
   icmp->seq = 0;

//   memcpy(packet + 20, &icmp, sizeof(struct icmphdr));

   sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
   if (sock == -1)
      printe("socket");

#ifndef IP_HDRINCL
   printe("raw");
#endif
   stat = sendto(sock, packet, sizeof(struct iphdr) + sizeof(struct icmphdr), 0, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   if (stat == -1)
      printe("send");

   puts("SUCCESS");
   for(i = 0; i < (sizeof(struct iphdr) + sizeof(struct icmphdr)); i++){
      printf("%2x", packet[i]);
      if(i % 2 != 0)
         printf(" ");
   }
   printf("\n");

   return 0;
}

uint16_t checksum(uint16_t * packet, int len){
   int i;
   uint16_t *tmp, sum = 0;
   tmp = packet;

   for (i = 0; i < len; i+=2)
      sum+=*tmp++;
   
   printf("%x\n", ~sum); 
   return ~sum;
}
void printe(const char *msg){
   printf("%s: %m\n", msg);
   exit(EXIT_FAILURE);
}
