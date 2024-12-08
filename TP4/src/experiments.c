#include "process.h"

FILE *output_file;
int file_index = 1;

void experiment(process_t *processes, int nb_processes, int optimal_solution)
{
   int ordonnancement_sorted[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      ordonnancement_sorted[i] = i;
   }

   int ordonnancement[nb_processes];
   int *ordonnancement_ptr = ordonnancement;

   memcpy(ordonnancement_ptr, ordonnancement_sorted, nb_processes * sizeof(int));
   constructive_heuristique(ordonnancement_ptr, processes, nb_processes);
   int constructive_delay = sum_total_delay(processes, nb_processes, ordonnancement_ptr);
   double constructive_ratio = (double)constructive_delay / (double)optimal_solution;
   printf("Constructive heuristic delay (sort with delay): %d, ratio: %lf\n", constructive_delay, constructive_ratio);

   memcpy(ordonnancement_ptr, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement_ptr, processes, nb_processes);
   int hill_climbing_delay = sum_total_delay(processes, nb_processes, ordonnancement_ptr);
   double hill_climbing_ratio = (double)hill_climbing_delay / (double)optimal_solution;
   printf("Hill Climbing delay: %d, ratio: %lf\n", hill_climbing_delay, hill_climbing_ratio);

   memcpy(ordonnancement_ptr, ordonnancement_sorted, nb_processes * sizeof(int));
   vnd(ordonnancement_ptr, processes, nb_processes, 100000);
   int vnd_delay = sum_total_delay(processes, nb_processes, ordonnancement_ptr);
   double vnd_ratio = (double)vnd_delay / (double)optimal_solution;
   printf("VND delay: %d, ratio: %lf\n", vnd_delay, vnd_ratio);

   char buf[64];
   sprintf(buf, "%d %d %d %d %d\n", file_index, constructive_delay, hill_climbing_delay, vnd_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, output_file);
   file_index++;
}

void file_experiment(char *path, int optimal_solution)
{
   process_file_t *process_file = parse_process_file(path);
   printf("Optimal solution: %d\n", optimal_solution);
   experiment(process_file->processes, process_file->nb_processes, optimal_solution);
   printf("----------------------\n");
   free(process_file->processes);
   free(process_file);
}

int main(void)
{

   int files_100[] = {15, 16, 17, 18, 19, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 85, 86, 87, 88, 89};
   int nb_files = sizeof(files_100) / sizeof(int);
   int solutions[nb_files];
   parse_solutions_file("SMTWP/solutions.txt", solutions, nb_files);

   output_file = fopen("experiments/output.dat", "w");
   if (output_file == NULL)
   {
      return -1;
   }

   for (int i = 0; i < nb_files; i++)
   {
      char buf[32];
      sprintf(buf, "SMTWP/n100_%d_b.txt", files_100[i]);
      file_experiment(buf, solutions[i]);
   }

   // // int files_1000[] = {1, 2};
   // for (int i = 0; i < (int)(sizeof(files_1000) / sizeof(int)); i++)
   // {
   //    char buf[32];
   //    sprintf(buf, "SMTWP/n1000_%d_b.txt", files_1000[i]);
   //    file_experiment(buf);
   // }

   fclose(output_file);
   return 0;
}