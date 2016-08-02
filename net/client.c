#include <sys/socket.h>
//#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
   int sfd;
   struct sockaddr_in dest;

   dest.sin_family = AF_INET;
   dest.sin_port = htons(8787);
   dest.sin_addr.s_addr = inet_addr(argv[1]);

   sfd = socket(AF_INET, SOCK_STREAM, 0);

   puts("socket ready");
   getchar();

   connect(sfd, (struct sockaddr *)&dest, sizeof(struct sockaddr));
   
   puts("connection ready");
   getchar();

   write(sfd, "HAI", 4);

   puts("exiting");
   getchar();

   return 0;
}
