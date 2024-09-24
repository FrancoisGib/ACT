#include "tablet.h"
#include <time.h>

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
   return 0;
}