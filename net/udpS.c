#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(){
   int sfd;
   char buf[10], buf_tx[10];
   socklen_t len;
   struct sockaddr_in local, src;
   pid_t rx_pid;
   socklen_t rx_len;

   local.sin_family = AF_INET;
   local.sin_port = htons(8585);
   local.sin_addr.s_addr = 0;

   memset(&src, 0, sizeof(struct sockaddr));
   
   sfd = socket(AF_INET, SOCK_DGRAM, 0);

   bind(sfd, (struct sockaddr *)&local, sizeof(struct sockaddr));

   rx_len = sizeof(struct sockaddr);

   for(;;){
   memset(buf, 0, 10);   
   recvfrom(sfd, buf, 10, 0, (struct sockaddr *)&src, &rx_len);
   printf("\n%s> %s\n", inet_ntoa(src.sin_addr), buf);

   sleep(3);
   sendto(sfd, "ACK", 4, 0, (struct sockaddr *)&src, sizeof(struct sockaddr));
   }
   /*   rx_pid = fork();
   if (rx_pid == 0){
      for(;;){
         memset(buf, 0, 10);

         recvfrom(sfd, buf, 10, 0, (struct sockaddr *)&src, &rx_len);
         printf("\n%s> %s\n> ", inet_ntoa(src.sin_addr), buf);

//         printf("sendto %m\n"); 
//         sendto(sfd, "SUC", 4, 0, (struct sockaddr *)&src, sizeof(struct sockaddr));
//         printf("sendto %m\n"); 
      }
   }else{
      for(;;){
         memset(buf_tx, 0, 10);
         printf("> ");
//         scanf("%s", buf_tx);

         sleep(5);
      
         len = strlen(buf_tx);
         sendto(sfd, "ACK", 4, 0, (struct sockaddr *)&src, sizeof(struct sockaddr));
      }
   }
*/
   return 0;
}
