#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main(){
   useconds_t delay = 200 * 1000;
   time_t stat;
   double proc;

   for ( ; ; ){
      stat = time(0);
      printf("FPS %s", ctime(&stat));
      usleep(delay);  
   }

   return 0;
}
