#include "tablet.h"
#include <time.h>

int main()
{
   tablet_t tablet;
   tablet.m = 3;
   tablet.n = 1;
   tablet.point.i = 2;
   tablet.point.j = 0;
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
   start = clock();
   // res = calculate_configuration_dynamic_init(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   // printf("Dynamic : %d, time : %lf\n", res, cpu_time_used);
   //  calculate_all_configurations_equals_x(tablet, 191);

   start = clock();
   res = calculate_configuration_dynamic_init_symetric(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("Dynamic symetric : %d, time : %lf\n", res, cpu_time_used);
   return 0;
}