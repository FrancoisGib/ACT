#include "tablet.h"
#include <time.h>
#include <string.h>

extern int memory_used;
extern int table_size;

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

   long sum_memory_dynamic = 0;
   long sum_memory_dynamic_symetric = 0;
   long sum_memory_hashmap = 0;
   double sum_time_dynamic = 0;
   double sum_time_dynamic_symetric = 0;
   double sum_time_hashmap = 0;
   printf("Dynamic | Dynamic symetric | Hashmap\n");
   for (int i = 1; i < tablet.m - 1; i++)
   {
      tablet.point.i = i;
      tablet.point.j = tablet.m - 1 - i;

      memory_used = 0;
      start = clock();
      int res_dynamic = calculate_configuration_dynamic_init(tablet);
      end = clock();
      cpu_time_used_dynamic = ((double)(end - start)) / CLOCKS_PER_SEC;
      int dynamic_memory_used = memory_used;
      sum_memory_dynamic += dynamic_memory_used;
      sum_time_dynamic += cpu_time_used_dynamic;

      memory_used = 0;
      start = clock();
      int res_dynamic_symetric = calculate_configuration_dynamic_init_symetric(tablet);
      end = clock();
      cpu_time_used_dynamic_symetric = ((double)(end - start)) / CLOCKS_PER_SEC;
      int dynamic_symetric_memory_used = memory_used;
      sum_memory_dynamic_symetric += dynamic_symetric_memory_used;
      sum_time_dynamic_symetric += cpu_time_used_dynamic_symetric;

      memory_used = 0;
      start = clock();
      int res_hashmap = calculate_configuration_hash_init(tablet);
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

      printf("(%d, %d)\nCPU (seconds): %.4lf, %.4lf, %.4lf\nMemory (octets): %d %d %d\nRes : %d %d %d\n\n", i, tablet.m - 1 - i, cpu_time_used_dynamic, cpu_time_used_dynamic_symetric, cpu_time_used_hashmap, dynamic_memory_used, dynamic_symetric_memory_used, hashmap_memory_used, res_dynamic, res_dynamic_symetric, res_hashmap);
   }
   fclose(memory_file);
   fclose(time_file);

   sum_memory_dynamic = ldiv(sum_memory_dynamic, 1000000L).quot,
   sum_memory_dynamic_symetric = ldiv(sum_memory_dynamic_symetric, 1000000L).quot,
   sum_memory_hashmap = ldiv(sum_memory_hashmap, 1000000L).quot,

   printf("Dynamic :\n\
         %.2lf seconds\n\
         %ld mo\n\n",
          sum_time_dynamic, sum_memory_dynamic);
   printf("Dynamic symetric :\n\
         %.2lf seconds\n\
         %ld mo\n\n",
          sum_time_dynamic_symetric, sum_memory_dynamic_symetric);
   printf("Hashmap :\n\
         %.2lf seconds\n\
         %ld mo\n",
          sum_time_hashmap, sum_memory_hashmap);
}

void find_pairs_with_value_x(int m, int n, int x)
{
   tablet_t tablet = {m, n, {0, 0}};
   int16_t ****array = init_array(m, n, m / 2 + 1, n / 2 + 1);
   for (int i = 0; i < m / 2 + 1; i++)
   {
      for (int j = 0; j < n / 2; j++)
      {
         tablet.point.i = i;
         tablet.point.j = j;
         if (calculate_configuration_dynamic_symetric(tablet, array) == x)
         {
            printf("(%d, %d)\n", tablet.point.i, tablet.point.j);
            printf("(%d, %d)\n", tablet.point.j, tablet.point.i);
            printf("(%d, %d)\n", m - 1 - tablet.point.i, n - 1 - tablet.point.j);
            printf("(%d, %d)\n", n - 1 - tablet.point.j, m - tablet.point.i);
         }
      }
   }
   free_array(array, m, n, m / 2 + 1, n / 2 + 1);
}

int main()
{
   // find_pairs_with_value_x(127, 127, 127);
   printf("\n\n");
   table_size = TABLE_3;
   generate_experimentations();
   return 0;
}