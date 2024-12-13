#include "process.h"

FILE *delay_file;
FILE *ratio_file;
FILE *constructive_heuristique_file;
FILE *hill_climbing_file;
FILE *ils_file;
int file_index = 1;

double constructive_heuristic_ratio = 0;
double limit_time_value_function_ratio = 0;
double weight_times_1_over_limit_ratio = 0;
double sum_delay_value_function_ratio = 0;
double weight_over_time_value_function_ratio = 0;
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
   constructive_heuristic_ratio += (double)constructive_delay / (double)optimal_solution;

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, limit_time_value_function);
   int limit_time_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);
   limit_time_value_function_ratio += (double)limit_time_value_function_delay / (double)optimal_solution;

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, weight_times_1_over_limit);
   int weight_times_1_over_limit_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);
   weight_times_1_over_limit_ratio += (double)weight_times_1_over_limit_delay / (double)optimal_solution;

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, sum_delay_value_function);
   int sum_delay_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);
   sum_delay_value_function_ratio += (double)sum_delay_value_function_delay / (double)optimal_solution;

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   memcpy(processes_copy, processes, nb_processes * sizeof(process_t));
   quicksort(processes_copy, 0, nb_processes - 1, weight_over_time_value_function);
   int weight_over_time_value_function_delay = sum_total_delay(processes_copy, nb_processes, ordonnancement);
   weight_over_time_value_function_ratio += (double)weight_over_time_value_function_delay / (double)optimal_solution;

   char buf[64];
   sprintf(buf, "%d %d %d %d %d %d %d\n", file_index, constructive_delay, limit_time_value_function_delay, weight_times_1_over_limit_delay, sum_delay_value_function_delay, weight_over_time_value_function_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, constructive_heuristique_file);
}

void hill_climbing_experiments(process_t *processes, int nb_processes, int optimal_solution)
{
   if (hill_climbing_file == NULL)
   {
      return;
   }

   int ordonnancement_sorted[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      ordonnancement_sorted[i] = i;
   }

   int ordonnancement[nb_processes];

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_symetric);
   int swap_symetric_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_middle);
   int swap_i_and_middle_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_nb_processes_div_2);
   int swap_i_and_i_plus_nb_processes_div_2_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1);
   int swap_i_and_i_plus_1_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_random);
   int swap_random_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, shift_left);
   int shift_left_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, shift_right);
   int shift_right_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_sub_list_nb_processes_per_4);
   int swap_sub_list_nb_processes_per_4_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_random_nb_processes_per_4);
   int swap_random_nb_processes_per_4_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, shift_left_lasts_i);
   int shift_left_lasts_i_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_sub_list);
   int swap_sub_list_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_three_times);
   int swap_i_and_i_plus_1_three_times_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_five_times);
   int swap_i_and_i_plus_1_five_times_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   char buf[128];
   sprintf(buf, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", file_index, swap_symetric_delay, swap_i_and_middle_delay, swap_i_and_i_plus_nb_processes_div_2_delay, swap_i_and_i_plus_1_delay, swap_random_delay, shift_left_delay, shift_right_delay, swap_sub_list_nb_processes_per_4_delay, swap_random_nb_processes_per_4_delay, shift_left_lasts_i_delay, swap_sub_list_delay, swap_i_and_i_plus_1_three_times_delay, swap_i_and_i_plus_1_five_times_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, hill_climbing_file);
}

void ils_experiments(process_t *processes, int nb_processes, int optimal_solution)
{
   if (ils_file == NULL)
   {
      return;
   }

   int ordonnancement_sorted[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      ordonnancement_sorted[i] = i;
   }

   int ordonnancement[nb_processes];

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   ils(ordonnancement, processes, nb_processes, swap_symetric);
   int swap_symetric_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   ils(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_three_times);
   int swap_i_and_i_plus_1_three_times_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   ils(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_five_times);
   int swap_i_and_i_plus_1_five_times_delay = sum_total_delay(processes, nb_processes, ordonnancement);

   char buf[64];
   sprintf(buf, "%d %d %d %d %d\n", file_index, swap_symetric_delay, swap_i_and_i_plus_1_three_times_delay, swap_i_and_i_plus_1_five_times_delay, optimal_solution);
   fwrite(buf, strlen(buf), 1, ils_file);
}

double hill_climbing_global_ratio = 0;
double vnd_global_ratio = 0;
double ils_global_ratio = 0;
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
   hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1);
   int hill_climbing_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double hill_climbing_ratio = (double)hill_climbing_delay / (double)optimal_solution;
   hill_climbing_global_ratio += hill_climbing_ratio;
   printf("Hill Climbing delay: %d, ratio: %lf\n", hill_climbing_delay, hill_climbing_ratio);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   vnd(ordonnancement, processes, nb_processes);
   int vnd_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double vnd_ratio = (double)vnd_delay / (double)optimal_solution;
   vnd_global_ratio += vnd_ratio;
   printf("VND delay: %d, ratio: %lf\n", vnd_delay, vnd_ratio);

   memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
   ils(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_three_times);
   int ils_delay = sum_total_delay(processes, nb_processes, ordonnancement);
   double ils_ratio = (double)ils_delay / (double)optimal_solution;
   ils_global_ratio += ils_ratio;
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
   hill_climbing_experiments(process_file->processes, process_file->nb_processes, optimal_solution);
   ils_experiments(process_file->processes, process_file->nb_processes, optimal_solution);
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
   ratio_file = fopen("experiments/ratio.dat", "w");
   constructive_heuristique_file = fopen("experiments/constructive_heuristic.dat", "w");
   ils_file = fopen("experiments/ils.dat", "w");
   hill_climbing_file = fopen("experiments/hill_climbing.dat", "w");
   for (int i = 0; i < nb_files; i++)
   {
      char buf[32];
      sprintf(buf, "SMTWP/n100_%d_b.txt", files_100[i]);
      file_experiment(buf, solutions[i]);
   }

   constructive_heuristic_ratio /= nb_files;
   limit_time_value_function_ratio /= nb_files;
   weight_times_1_over_limit_ratio /= nb_files;
   sum_delay_value_function_ratio /= nb_files;
   weight_over_time_value_function_ratio /= nb_files;

   printf("Constructive: %lf\nlimit_time_value: %lf\nweight times 1 over limit: %lf\nsum delay: %lf\nweight over time: %lf\n", constructive_heuristic_ratio, limit_time_value_function_ratio, weight_times_1_over_limit_ratio, sum_delay_value_function_ratio, weight_over_time_value_function_ratio);
   hill_climbing_global_ratio /= nb_files;
   vnd_global_ratio /= nb_files;
   ils_global_ratio /= nb_files;
   printf("Hill climbing: %lf\nVND: %lf\nILS: %lf\n", hill_climbing_global_ratio, vnd_global_ratio, ils_global_ratio);
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
   fclose(hill_climbing_file);
   fclose(ils_file);
   printf("\n");
   return 0;
}