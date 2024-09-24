#include "tablet.h"
#include <time.h>
#include <string.h>

extern int memory_used;

int main()
{
   tablet_t tablet;
   tablet.m = 51;
   tablet.n = 51;
   tablet.point.i = 25;
   tablet.point.j = 25;
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
   // calculate_all_configurations_equals_x(tablet, 191);
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

   FILE *file = fopen("output.dat", "w");
   tablet.m = 51;
   tablet.n = 51;
   for (int i = 1; i < tablet.m - 1; i++)
   {
      tablet.point.i = i;
      tablet.point.j = tablet.m - 1 - i;

      memory_used = 0;
      calculate_configuration_dynamic_init(tablet);
      int dynamic_memory_used = memory_used;

      tablet.point.i = i;
      tablet.point.j = tablet.m - 1 - i;

      memory_used = 0;
      calculate_configuration_dynamic_init_symetric(tablet);
      int dynamic_symetric_memory_used = memory_used;
      char buf[100];
      printf("(%d %d), dynamic : %d bytes, dynamic symetric :  %d bytes\n", tablet.point.i, tablet.point.j, dynamic_memory_used, dynamic_symetric_memory_used);
      sprintf(buf, "%d %d %d\n", tablet.point.i, dynamic_memory_used, dynamic_symetric_memory_used);
      fwrite(buf, strlen(buf), 1, file);
   }
   fclose(file);
   return 0;
}