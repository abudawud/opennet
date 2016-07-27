#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define UDP 17
//#define DATA   100
static int sfd;

void ignore(int ign);

int main(int argc, char *argv[]){
   const char 
      *node = argv[1],
      *service = argv[2];

   unsigned char *dmsg;
   int stat, i,DATA;

   struct sockaddr *address;
   struct addrinfo hints;
   struct addrinfo *result;

   DATA = atoi(argv[3]);
   dmsg = malloc(sizeof(char) * DATA);   
   printf("%s %s size %d\n", node, service, DATA);
   memset(&hints, 0, sizeof(struct addrinfo));
   memset(dmsg, 0x54, sizeof(char) * DATA);

//   printf("%s\n",dmsg);
//   exit(1);

   hints.ai_flags = 0;
   hints.ai_family = AF_INET;
   hints.ai_socktype = SOCK_DGRAM;
   hints.ai_protocol = 0;
   
   stat = getaddrinfo(node, service, &hints, &result);
   if (stat != 0){
      printf("error: %s\n", gai_strerror(stat));
      exit(EXIT_FAILURE);
   }else
      puts("Address Available");
   
   address = result->ai_addr;

   i = 0;
   while (i++ < 14)
   printf("%d\n",address->sa_data[i]);

   sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
   if (sfd == -1){
      printf("error : %m\n");
      exit(EXIT_FAILURE);
   }else
      printf("Socket created on fd %d\n", sfd);

   stat = connect(sfd, result->ai_addr, result->ai_addrlen);
   if (stat != 0){
      printf("error : %m\n");
      exit(EXIT_FAILURE);
   }else
      printf("Connected to %s on %s\n", node, service);
   
//   puts("Ready to send");
//   getchar();

   puts("\nSending Messege...\n");
   while(1){
   stat = write(sfd, dmsg, sizeof(char) * DATA); 
   signal(SIGINT, ignore);
  // usleep(1);
   }

   return 0;
}

void ignore(int ign){
   
   puts("program quit\n");
   
   if (close(sfd) == 0)
      puts("socket closed");
   else
      printf("error closing socket : %m\n");

   getchar();
   exit(EXIT_SUCCESS);
}
