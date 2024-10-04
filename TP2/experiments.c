#include "tablet.h"
#include <time.h>
#include <string.h>

extern int memory_used;

void generate_experimentations()
{
   tablet_t tablet;
   tablet.m = 51;
   tablet.n = 51;
   tablet.point.i = 25;
   tablet.point.j = 25;
   int res;
   clock_t start, end;
   double cpu_time_used_dynamic, cpu_time_used_dynamic_symetric, cpu_time_used_hashmap;

   FILE *memory_file = fopen("./gnuplot/memory.dat", "w");
   FILE *time_file = fopen("./gnuplot/time.dat", "w");

   long int sum_memory_dynamic, sum_memory_dynamic_symetric, sum_memory_hashmap;
   double sum_time_dynamic, sum_time_dynamic_symetric, sum_time_hashmap;
   for (int i = 1; i < tablet.m - 1; i++)
   {
      tablet.point.i = i;
      tablet.point.j = tablet.m - 1 - i;

      memory_used = 0;
      start = clock();
      res = calculate_configuration_dynamic_init(tablet);
      end = clock();
      cpu_time_used_dynamic = ((double)(end - start)) / CLOCKS_PER_SEC;
      int dynamic_memory_used = memory_used;
      sum_memory_dynamic += dynamic_memory_used;
      sum_time_dynamic += cpu_time_used_dynamic;

      memory_used = 0;
      start = clock();
      calculate_configuration_dynamic_init_symetric(tablet);
      end = clock();
      cpu_time_used_dynamic_symetric = ((double)(end - start)) / CLOCKS_PER_SEC;
      int dynamic_symetric_memory_used = memory_used;
      sum_memory_dynamic_symetric += dynamic_symetric_memory_used;
      sum_time_dynamic_symetric += cpu_time_used_dynamic_symetric;

      memory_used = 0;
      start = clock();
      calculate_configuration_hash_init(tablet);
      end = clock();
      cpu_time_used_hashmap = ((double)(end - start)) / CLOCKS_PER_SEC;
      int hashmap_memory_used = memory_used;
      sum_memory_hashmap += hashmap_memory_used;
      sum_time_hashmap += cpu_time_used_hashmap;

      char buf[128];
      sprintf(buf, "%d %d %d %d\n", tablet.point.i, dynamic_memory_used, dynamic_symetric_memory_used, hashmap_memory_used);
      fwrite(buf, strlen(buf), 1, memory_file);

      sprintf(buf, "%d %lf %lf %lf\n", tablet.point.i, cpu_time_used_dynamic, cpu_time_used_dynamic_symetric, cpu_time_used_hashmap);
      fwrite(buf, strlen(buf), 1, time_file);
   }
   fclose(memory_file);
   fclose(time_file);

   double symetric_acceleration = 100 * sum_time_dynamic / sum_time_dynamic_symetric;
   double symetric_memory_percent = (double)sum_memory_dynamic_symetric * 100 / (double)sum_memory_dynamic;
   double hashmap_memory_percent = (double)sum_memory_dynamic * 100 / (double)sum_memory_hashmap;
   double symetric_acceleration_over_hashmap = 100 * sum_time_hashmap / sum_time_dynamic_symetric;
   printf("Mémoire gagnée par les symétries (en %%) : %lf, accélération : %lf\nMémoire gagnée avec la hashmap (en %%) : %lf, accélération par le tableau et symétrie : %lf\n", symetric_memory_percent, symetric_acceleration, hashmap_memory_percent, symetric_acceleration_over_hashmap);
}

int main()
{
   generate_experimentations();
   return 0;
}