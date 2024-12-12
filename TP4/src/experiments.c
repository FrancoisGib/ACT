#include "process.h"

FILE *delay_file;
FILE *ratio_file;
FILE *constructive_heuristique_file;
int file_index = 1;

void constructive_heuristique_experiments(process_t *processes, int nb_processes, int optimal_solution)
{
   if (constructive_heuristique_file == NULL)
   {
      return;
   }

   int ordonnancement_sorted[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      ordonnancement_sorted[i] = i;
   }

   int ordonnancement[nb_processes];

   process_t processes_copy[nb_processes];
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   constructive_heuristique(ordonnancement, processes_copy, nb_processes);
   int constructive_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, limit_time_value_function);
   int limit_time_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, weight_times_1_over_limit);
   int weight_times_1_over_limit_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, sum_delay_value_function);
   int sum_delay_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, weight_over_time_value_function);
   int weight_over_time_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);

   char buf[64];
   sprintf(buf, "%d %d %d %d %d %d %d\n", file_index, constructive_delay, limit_time_value_function_delay, weight_times_1_over_limit_delay, sum_delay_value_function_delay, weight_over_time_value_function_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, constructive_heuristique_file);
}

void experiment(process_t *processes, int nb_processes, int optimal_solution)
{
   int ordonnancement_sorted[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      ordonnancement_sorted[i] = i;
   }

   int ordonnancement[nb_processes];

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   constructive_heuristique(ordonnancement, processes, nb_processes);
   int constructive_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double constructive_ratio = (double)constructive_delay / (double)optimal_solution;
   printf("Constructive heuristic delay (sort with delay): %d, ratio: %lf\n", constructive_delay, constructive_ratio);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes);
   int hill_climbing_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double hill_climbing_ratio = (double)hill_climbing_delay / (double)optimal_solution;
   printf("Hill Climbing delay: %d, ratio: %lf\n", hill_climbing_delay, hill_climbing_ratio);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   vnd(ordonnancement, processes, nb_processes);
   int vnd_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double vnd_ratio = (double)vnd_delay / (double)optimal_solution;
   printf("VND delay: %d, ratio: %lf\n", vnd_delay, vnd_ratio);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   ils(ordonnancement, processes, nb_processes);
   int ils_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double ils_ratio = (double)ils_delay / (double)optimal_solution;
   printf("ILS delay: %d, ratio: %lf\n", ils_delay, ils_ratio);

   char buf[64];
   sprintf(buf, "%d %d %d %d %d %d\n", file_index, constructive_delay, hill_climbing_delay, vnd_delay, ils_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, delay_file);

   memset(buf, 0, 64);
   sprintf(buf, "%d %lf %lf %lf %lf %lf\n", file_index, constructive_ratio, hill_climbing_ratio, vnd_ratio, ils_ratio, 1.0);
   fwrite(buf, strlen(buf), 1, ratio_file);
   file_index++;
}

void file_experiment(char *path, int optimal_solution)
{
   process_file_t *process_file = parse_process_file(path);
   printf("Optimal solution: %d\n", optimal_solution);
   constructive_heuristique_experiments(process_file->processes, process_file->nb_processes, optimal_solution);
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

   delay_file = fopen("experiments/delay.dat", "w");
   if (delay_file == NULL)
   {
      return -1;
   }
   ratio_file = fopen("experiments/ratio.dat", "w");
   if (ratio_file == NULL)
   {
      fclose(delay_file);
      return -1;
   }
   constructive_heuristique_file = fopen("experiments/constructive_heuristique.dat", "w");
   if (constructive_heuristique_file == NULL)
   {
      fclose(ratio_file);
      fclose(delay_file);
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

   fclose(delay_file);
   fclose(ratio_file);
   fclose(constructive_heuristique_file);
   return 0;
}