#include <stdio.h>
#include <omp.h>

int main ()
{
   #pragma omp parallel //parallel region with default number of threads
   {
      int ID = omp_get_thread_num(); //return thread ID running this code

      printf("hello(%d) ", ID);
      printf("world(%d)\n",ID);
   }//end of the parallel region
}
