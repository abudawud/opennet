#include <sys/socket.h>
#include <netinet/in.h>

int main(){
   int sfd;
   char buf[10];

   struct sockaddr_in local, dest;

   local.sin_family = AF_INET;
   local.sin_port = htons(8585);
   local.sin_addr.s_addr = 0;

   sfd = socket(AF_INET, SOCK_DGRAM, 0);

   bind(sfd, (struct sockaddr *)&local, sizeof(struct sockaddr));

   while (1){
      memset(buf, 0, 10);
      recv(sfd, buf, 10, 0);
      printf("rec : %s\n", buf);
   }

   return 0;
}

