#include "tablet.h"
#include <time.h>
#include <string.h>

extern int nb_allocations;

int main()
{
   tablet_t tablet;
   tablet.m = 100;
   tablet.n = 100;
   tablet.point.i = 50;
   tablet.point.j = 50;
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
   nb_allocations = 0;
   start = clock();
   res = calculate_configuration_dynamic_init(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Dynamic : %d, time : %lf, number of allocations : %d\n", res, cpu_time_used, nb_allocations);

   nb_allocations = 0;
   start = clock();
   res = calculate_configuration_dynamic_init_symetric(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Dynamic symetric : %d, time : %lf, number of allocations : %d\n", res, cpu_time_used, nb_allocations);

   /*nb_allocations = 0;
   FILE *file = fopen("output.dat", "w");
   tablet.m = 50;
   tablet.n = 50;
   for (int i = 0; i < tablet.m; i++)
   {
      tablet.point.i = i;
      tablet.point.j = tablet.m - 1 - i;
      calculate_configuration_dynamic_init_symetric(tablet);
      char buf[32];
      sprintf(buf, "%d %d\n", tablet.point.i, nb_allocations);
      fwrite(buf, strlen(buf), 1, file);
      nb_allocations = 0;
   }
   fclose(file);*/
   return 0;
}