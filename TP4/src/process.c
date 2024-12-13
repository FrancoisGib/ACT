#include "process.h"

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

typedef struct
{
   int **neighbors;
   int nb_neighbors;
} neighbors_t;

void generate_neighbors_swap(neighbors_t *neighbors_info, int *ordonnancement, int nb_processes, swap_function swap_func)
{
   neighbors_info->nb_neighbors = nb_processes - 1;
   neighbors_info->neighbors = malloc(neighbors_info->nb_neighbors * sizeof(int *));
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
      neighbors_info->neighbors[i] = neighbor;
      // Copy all tasks
      memcpy(neighbor, ordonnancement, nb_processes * sizeof(int));
      // Swap
      swap_func(neighbor, sorted_ordonnancement, nb_processes, i);
   }
}
void generate_neighbors(neighbors_t *neighbors_info, int *ordonnancement, int nb_processes, swap_function swap_func)
{
   neighbors_info->nb_neighbors = nb_processes * nb_processes;

   neighbors_info->neighbors = malloc(neighbors_info->nb_neighbors * sizeof(int *));

   int neighbor_index = 0;

   for (int i = 0; i < nb_processes; i++)
   {
      for (int j = 0; j < nb_processes; j++)
      {
         if (i == j)
            continue;

         int *new_neighbor = malloc(nb_processes * sizeof(int));
         memcpy(new_neighbor, ordonnancement, nb_processes * sizeof(int));
         int sorted_ordonnancement[nb_processes];
         // Sort tasks
         for (int l = 0; l < nb_processes; l++)
         {
            int found = 0;
            int k = 0;
            while (!found && k < nb_processes)
            {
               if (ordonnancement[k] == l)
               {
                  sorted_ordonnancement[l] = k;
                  found = 1;
               }
               k++;
            }
         }
         swap_func(new_neighbor, sorted_ordonnancement, nb_processes, i);

         neighbors_info->neighbors[neighbor_index] = new_neighbor;
         neighbor_index++;
      }
   }
   neighbors_info->nb_neighbors = neighbor_index - 1;
}

void hill_climbing(int *current_ordonnancement, process_t *processes, int nb_processes, swap_function swap_func)
{
   neighbors_t neighbors_info;
   generate_neighbors_swap(&neighbors_info, current_ordonnancement, nb_processes, swap_func);
   int current_ordonnancement_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
   int best_delay = current_ordonnancement_delay;
   int best_ordonnancement_index = -1;
   for (int i = 0; i < neighbors_info.nb_neighbors; i++)
   {
      int delay = sum_total_delay(processes, nb_processes, neighbors_info.neighbors[i]);
      if (delay < best_delay)
      {
         best_delay = delay;
         best_ordonnancement_index = i;
      }
   }

   if (best_ordonnancement_index != -1)
   {
      memcpy(current_ordonnancement, neighbors_info.neighbors[best_ordonnancement_index], nb_processes * sizeof(int));
   }

   for (int i = 0; i < neighbors_info.nb_neighbors; i++)
   {
      free(neighbors_info.neighbors[i]);
   }
   free(neighbors_info.neighbors);
}

int *get_best_neighbor_and_free(neighbors_t *neighbors_info, process_t *processes, int nb_processes)
{
   int best_delay = INT_MAX;
   int *best_neighbor = malloc(nb_processes * sizeof(int));
   for (int i = 0; i < neighbors_info->nb_neighbors; i++)
   {
      int *neighbor = neighbors_info->neighbors[i];
      int neighbor_delay = sum_total_delay(processes, nb_processes, neighbor);
      if (neighbor_delay < best_delay)
      {
         memcpy(best_neighbor, neighbor, nb_processes * sizeof(int));
         best_delay = neighbor_delay;
      }
      free(neighbor);
   }
   free(neighbors_info->neighbors);
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
//                                   swap_sub_list
//                                   swap_symetric,
//                                   swap_random,
//                                   swap_i_and_i_plus_1_three_times,
// };

swap_function swap_functions[] = {
    swap_i_and_i_plus_1,
    swap_i_and_middle,
    swap_symetric,
    swap_random_nb_processes_per_4,
    swap_random,
    swap_i_and_i_plus_1_three_times,
};

void vnd(int *current_ordonnancement, process_t *processes, int nb_processes)
{
   int nb_swap_function = sizeof(swap_functions) / sizeof(swap_function);
   int i = 0;
   int current_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
   while (i < nb_swap_function)
   {
      neighbors_t neighbors_info;
      generate_neighbors_swap(&neighbors_info, current_ordonnancement, nb_processes, swap_functions[i]);
      int *best_neighbor = get_best_neighbor_and_free(&neighbors_info, processes, nb_processes);
      hill_climbing(best_neighbor, processes, nb_processes, swap_i_and_i_plus_1);
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

void perturbation(int *current_ordonnancement, process_t *processes, int nb_processes, int k, swap_function swap_func)
{
   int sorted_ordonnancement[nb_processes];
   for (int i = 0; i < nb_processes; i++)
   {
      int found = 0;
      int j = 0;
      while (!found && j < nb_processes)
      {
         if (current_ordonnancement[j] == i)
         {
            sorted_ordonnancement[i] = j;
            found = 1;
         }
         j++;
      }
   }
   swap_func(current_ordonnancement, sorted_ordonnancement, nb_processes, k);
}

typedef int (*accept_function)(int *, process_t *, int);

int n_iter = 1000;
int accept_count = 0;

int accept_n_iterations_impl(int *current_ordonnancement, process_t *processes, int nb_processes)
{
   accept_count++;
   if (accept_count >= n_iter)
   {
      accept_count = 0;
      return 1;
   }
   return 0;
}

accept_function accept_n_iterations(int n)
{
   n_iter = n;
   return accept_n_iterations_impl;
}

int n_sec = 10;
void accept_n_sec_gen(int n)
{
   n_sec = n;
}

clock_t accept_time = 0;
int accept_n_sec(int *current_ordonnancement, process_t *processes, int nb_processes)
{
   if (accept_time == 0)
   {
      accept_time = clock();
   }
   clock_t current_time = clock();
   int time_used = ((current_time - accept_time)) / CLOCKS_PER_SEC;
   if (time_used >= n_sec)
   {
      accept_time = 0;
      return 1;
   }
   return 0;
}

void ils(int *current_ordonnancement, process_t *processes, int nb_processes, swap_function swap_func)
{
   accept_function accept = accept_n_iterations(10000);
   int i = 0;
   int best_ordonnancement[nb_processes];
   memcpy(best_ordonnancement, current_ordonnancement, nb_processes * sizeof(int));
   int best_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
   while (!accept(current_ordonnancement, processes, nb_processes))
   {
      vnd(current_ordonnancement, processes, nb_processes);
      int current_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
      if (current_delay < best_delay)
      {
         best_delay = current_delay;
         memcpy(best_ordonnancement, current_ordonnancement, nb_processes * sizeof(int));
      }
      perturbation(current_ordonnancement, processes, nb_processes, i % nb_processes, swap_func);
      i++;
   }
   memcpy(current_ordonnancement, best_ordonnancement, nb_processes * sizeof(int));
}