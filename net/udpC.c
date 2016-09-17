#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdint.h>

int main(int argc, char *argv[]){
   int sfd;
   char buf[10];
   uint8_t len;
   struct sockaddr_in dest;

   dest.sin_family = AF_INET;
<<<<<<< HEAD
   dest.sin_port = htons(8080);
   dest.sin_addr.s_addr = inet_addr("192.168.0.101");
=======
   dest.sin_port = htons(8585);
   dest.sin_addr.s_addr = inet_addr(argv[1]);
>>>>>>> 86a2bb89963d2f951c47bd55af42ba3fb48da83d

   sfd = socket(AF_INET, SOCK_DGRAM, 0);
   printf("socket %m\n");

   for(;;){
      memset(buf, 0, 10);
      printf("> ");
      scanf("%s", buf);
      len = strlen(buf);
      
      sendto(sfd, buf, len, 0, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   }

   printf("sendto %m\n");

   return 0;
}
