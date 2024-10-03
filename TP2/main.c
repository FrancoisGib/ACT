#include "tablet.h"
#include <time.h>
#include <string.h>

extern int memory_used;

int main(int argc, char **argv)
{
   tablet_t tablet;
   if (argc < 5)
   {
      tablet.m = 10;
      tablet.n = 7;
      tablet.point.i = 7;
      tablet.point.j = 3;
      printf("Configuration par défaut (%d %d), (%d %d)\n", tablet.m, tablet.n, tablet.point.i, tablet.point.j);
   }
   else
   {
      int m = atoi(argv[1]);
      int n = atoi(argv[2]);
      int i = atoi(argv[3]);
      int j = atoi(argv[4]);
      printf("%d %d %d %d\n", m, n, i, j);
      if (!(m > i && n > j))
      {
         printf("Configuration invalide\n");
         exit(0);
      }
      tablet.m = m;
      tablet.n = n;
      tablet.point.i = i;
      tablet.point.j = j;
   }
   // calculate_all_configurations_equals_x(tablet, 127);

   int res;
   clock_t start, end;
   double cpu_time_used;

   /*
   start = clock();
   res = calculate_configuration(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Basic recursive : %d, time : %lf\n", res, cpu_time_used);
   */

   /*
      memory_used = 0;
      start = clock();
      res = calculate_configuration_dynamic_init(tablet);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Dynamic : %d, time : %lf, memory used : %d bytes\n", res, cpu_time_used, memory_used);

      memory_used = 0;
      start = clock();
      res = calculate_configuration_dynamic_init_symetric(tablet);
      end = clock();
      cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
      printf("Dynamic symetric : %d, time : %lf, memory used : %d bytes\n", res, cpu_time_used, memory_used);
   */
   game(tablet);
   return 0;
}