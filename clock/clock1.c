#include <stdio.h>   // printf, puts, scanf, ...
#include <time.h>    // clock, time, ctime, ...
#include <unistd.h>  // usleep, sleep, ... /* use windows.h on win */
#include <stdint.h>  // uint8_t, int32_t, ...

#define MICROS(X) (X * 1000000)
#define MFPS      5  //frame rate per-second
#define DELAY     MICROS((float)1 / MFPS)   // max delay for 5 frame-limit in miliseconds.

int main(){
   uint8_t i;
   time_t ct;
   clock_t start, end;
   int32_t rate, load[8];
   uint8_t fps = 5;
   useconds_t delay;
   register uint32_t counter;
   char * stime;

   printf("Load Level [1 - 8] :");
   scanf("%d", &i);

   load[0] = 0xf;
   load[1] = 0xff;
   load[2] = 0xfff;
   load[3] = 0xffff;
   load[4] = 0xfffff;
   load[5] = 0xffffff;
   load[6] = 0xfffffff;
   load[7] = 0xdfffffff;

   if (i > 8){
      puts("LEVEL TO HIGH!");
      return -1;
   }

   for ( ; ; ){
      start = clock();
      
      // load or proccess that need high cpu resource
      for ( counter = 0; counter < load[i - 1]; counter++);
      
      ct = time(0);
      stime = ctime(&ct);

      printf("FPS %s", stime);

      end = clock();
      rate = MICROS((float)(end - start) / CLOCKS_PER_SEC);

      if (rate > 0 && rate < DELAY)
         usleep(DELAY - rate);
      else if ( rate <= 0 )
         usleep(DELAY);
      else
         puts("RENDER ERROR");
   }
   return 0;
}

