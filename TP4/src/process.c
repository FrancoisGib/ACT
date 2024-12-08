#include "process.h"

// Functions used in the beginning in quicksort to make constructive heuristics, but not useful now
// double limit_time_value_function(process_t *process)
// {
//     return process->limit_time;
// }

// double weight_over_time_value_function(process_t *process)
// {
//     return (double)process->weight / (double)process->time;
// }

// double sum_delay_value_function(process_t *process)
// {
//     return (double)(process->limit_time * process->weight);
// }

// double weight_times_1_over_limit(process_t *process)
// {
//     return (double)((double)process->weight * (1 / (double)process->limit_time));
// }

int sum_total_delay(process_t *processes, int nb_processes, int *ordonnancement)
{
   int delay = 0;
   int current_time = 0;
   for (int i = 0; i < nb_processes; i++)
   {
      int task = ordonnancement[i];
      process_t process = processes[task];
      current_time += process.time;
      if (current_time - process.limit_time > 0)
         delay += (current_time - process.limit_time) * process.weight;
   }
   return delay;
}

void generate_random_solution(int *ordonnancement, int nb_processes)
{
   char already_ordonated[nb_processes];
   memset(already_ordonated, 0, nb_processes);

   int i = 0;
   while (i < nb_processes)
   {
      int random = rand() % nb_processes;
      if (!already_ordonated[random])
      {
         already_ordonated[random] = 1;
         ordonnancement[random] = i;
         i++;
      }
   }
}

void constructive_heuristique(int *ordonnancement, process_t *processes, int nb_processes)
{
   char already_taken[nb_processes];
   memset(already_taken, 0, nb_processes);
   int time = 0;
   for (int i = 0; i < nb_processes; i++)
   {
      int current_loss = INT_MAX;
      int index = -1;
      for (int j = 0; j < nb_processes; j++)
      {
         process_t process = processes[j];
         int take_loss = MAX(0, (process.limit_time - time + process.time) * (1 / process.weight));
         if ((take_loss < current_loss || index == -1) && !already_taken[j])
         {
            index = j;
            current_loss = take_loss;
         }
      }
      // Uncomment to print all losses
      // printf("loss: %d, time: %d, weight: %d limit: %d\n", current_loss, processes[index].time, processes[index].weight, processes[index].limit_time);
      already_taken[index] = 1;
      ordonnancement[i] = index;
   }
}

int **generate_neighbors(int *ordonnancement, int nb_processes, swap_function swap_func)
{
   int nb_neighbors = nb_processes - 1;
   int **neighbors = malloc(nb_neighbors * sizeof(int *));
   int sorted_ordonnancement[nb_processes];
   // Sort tasks
   for (int i = 0; i < nb_processes; i++)
   {
      int found = 0;
      int j = 0;
      while (!found && j < nb_processes)
      {
         if (ordonnancement[j] == i)
         {
            sorted_ordonnancement[i] = j;
            found = 1;
         }
         j++;
      }
   }

   for (int i = 0; i < nb_processes - 1; i++)
   {
      int *neighbor = malloc(nb_processes * sizeof(int));
      neighbors[i] = neighbor;
      // Copy all tasks
      memcpy(neighbor, ordonnancement, nb_processes * sizeof(int));
      // Swap
      swap_func(neighbor, sorted_ordonnancement, nb_processes, i);
   }
   return neighbors;
}

void hill_climbing(int *current_ordonnancement, process_t *processes, int nb_processes)
{
   int **neighbors = generate_neighbors(current_ordonnancement, nb_processes, swap_i_and_i_plus_1);
   int nb_ordonnancements = nb_processes - 1;
   int current_ordonnancement_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
   int best_delay = current_ordonnancement_delay;
   int best_ordonnancement_index = -1;
   for (int i = 0; i < nb_ordonnancements; i++)
   {
      int delay = sum_total_delay(processes, nb_processes, neighbors[i]);
      if (delay < best_delay)
      {
         best_delay = delay;
         best_ordonnancement_index = i;
      }
   }

   if (best_ordonnancement_index != -1)
   {
      memcpy(current_ordonnancement, neighbors[best_ordonnancement_index], nb_processes * sizeof(int));
   }

   for (int i = 0; i < nb_ordonnancements; i++)
   {
      free(neighbors[i]);
   }
   free(neighbors);
}

int *get_best_neighbor_and_free(int **neighbors, process_t *processes, int nb_processes)
{
   int nb_neighbors = nb_processes - 1;
   int best_delay = INT_MAX;
   int *best_neighbor = malloc(nb_processes * sizeof(int));
   for (int i = 0; i < nb_neighbors; i++)
   {
      int *neighbor = neighbors[i];
      int neighbor_delay = sum_total_delay(processes, nb_processes, neighbor);
      if (neighbor_delay < best_delay)
      {
         memcpy(best_neighbor, neighbor, nb_processes * sizeof(int));
         best_delay = neighbor_delay;
      }
      free(neighbor);
   }
   free(neighbors);
   return best_neighbor;
}

// Functions used for the generation of different neighborhoods, by order of small to big perturbation
// swap_function swap_functions[] = {swap_i_and_i_plus_1,
//                                   swap_i_and_middle,
//                                   swap_i_and_i_plus_nb_processes_div_2,
//                                   shift_left_lasts_i,
//                                   shift_left,
//                                   shift_right,
//                                   swap_sub_list_nb_processes_per_4,
//                                   swap_random_nb_processes_per_4,
//                                   swap_symetric,
//                                   swap_random};

swap_function swap_functions[] = {
    swap_i_and_i_plus_1,
    swap_i_and_middle,
    swap_symetric,
    swap_random_nb_processes_per_4,
    swap_random,
    swap_sub_list_nb_processes_per_4,
};

void vnd(int *current_ordonnancement, process_t *processes, int nb_processes)
{
   int nb_swap_function = sizeof(swap_functions) / sizeof(swap_function);
   int i = 0;
   int current_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
   while (i < nb_swap_function)
   {
      int **neighbors = generate_neighbors(current_ordonnancement, nb_processes, swap_functions[i]);
      int *best_neighbor = get_best_neighbor_and_free(neighbors, processes, nb_processes);
      hill_climbing(best_neighbor, processes, nb_processes);
      int neighbor_delay = sum_total_delay(processes, nb_processes, best_neighbor);
      if (neighbor_delay < current_delay)
      {
         current_delay = neighbor_delay;
         memcpy(current_ordonnancement, best_neighbor, nb_processes * sizeof(int));
         i = 0;
      }
      else
      {
         i++;
      }
      free(best_neighbor);
   }
}