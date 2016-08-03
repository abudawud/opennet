#include <sys/socket.h>
#include <stdio.h> 
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[]){
   int sfd, peerfd;
   unsigned char buf[10];
   socklen_t len, peer_len;

   struct sockaddr_in local, src, peer;

   memset(&src, 0, sizeof(struct sockaddr_in));
   len = sizeof(struct sockaddr_in);

   peer.sin_family = AF_INET;
   peer.sin_port = 0;
   peer.sin_addr.s_addr = 0;

   local.sin_family = AF_INET;
   local.sin_port = htons(8787);
   local.sin_addr.s_addr = inet_addr(argv[1]);

   sfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sfd == -1)
      printf("socket %m");

   bind(sfd, (struct sockaddr *)&local, sizeof(struct sockaddr));

   listen(sfd, 50);

   puts("waiting");
   peer_len = sizeof(struct sockaddr);
   peerfd = accept(sfd, (struct sockaddr *)&peer, &peer_len);

   puts("waiting messege(s)");
   recvfrom(peerfd, buf, 10, 0, (struct sockaddr *)&src, &len);
   printf("recvfrom %m\n");

   for(;;){
   sendto(peerfd, "SYSTEM INSECURE", 15, 0, (struct sockaddr *)&peer, sizeof(struct sockaddr));
   }

   printf("incoming from %s: %s\n", inet_ntoa(peer.sin_addr), buf);
   puts("complete");
   getchar();
   
   shutdown(sfd, SHUT_RDWR);
   shutdown(peerfd, SHUT_RDWR);

   return 0;
}
