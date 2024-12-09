#include "swap.h"

void swap(int *x, int *y)
{
   int temp = *x;
   *x = *y;
   *y = temp;
}

void swap_symetric(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes - 1 - i]] = i;
   ordonnancement[sorted_ordonnancement[i]] = nb_processes - 1 - i;
}

void swap_i_and_middle(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes / 2]] = i;
   ordonnancement[sorted_ordonnancement[i]] = nb_processes / 2;
}

void swap_i_and_i_plus_nb_processes_div_2(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[(nb_processes + (nb_processes / 2)) % nb_processes]] = i;
   ordonnancement[sorted_ordonnancement[i]] = (nb_processes + (nb_processes / 2)) % nb_processes;
}

void swap_i_and_i_plus_1(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes - 1]] = i;
   ordonnancement[sorted_ordonnancement[i]] = nb_processes - 1;
}

void swap_random(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int index1 = rand() % nb_processes;
   int index2 = rand() % nb_processes;

   while (index1 == index2)
   {
      index2 = rand() % nb_processes;
   }

   int temp = ordonnancement[sorted_ordonnancement[index1]];
   ordonnancement[sorted_ordonnancement[index1]] = ordonnancement[sorted_ordonnancement[index2]];
   ordonnancement[sorted_ordonnancement[index2]] = temp;
}

void shift_left(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int temp = ordonnancement[0];
   for (int j = 0; j < nb_processes - 1; j++)
   {
      ordonnancement[j] = ordonnancement[j + 1];
   }
   ordonnancement[nb_processes - 1] = temp;
}

void shift_left_lasts_i(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int temp = ordonnancement[0];
   for (int j = nb_processes - i; j < nb_processes; j++)
   {
      ordonnancement[j] = ordonnancement[j + 1];
   }
   ordonnancement[nb_processes - 1] = temp;
}

void shift_right(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int temp = ordonnancement[0];
   for (int j = 1; j < nb_processes; j++)
   {
      ordonnancement[j - 1] = ordonnancement[j];
   }
   ordonnancement[nb_processes - 1] = temp;
}

void swap_sub_list_nb_processes_per_4(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   if (i >= 3 * nb_processes / 4)
   {
      i -= nb_processes / 4;
   }
   swap_symetric(ordonnancement, sorted_ordonnancement, nb_processes, i);
}

void swap_random_nb_processes_per_4(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int num_swaps = nb_processes / 4;
   for (int j = 0; j < num_swaps; j++)
   {
      int index1 = rand() % nb_processes;
      int index2 = rand() % nb_processes;

      while (index1 == index2)
      {
         index2 = rand() % nb_processes;
      }
      int temp = ordonnancement[index1];
      ordonnancement[index1] = ordonnancement[index2];
      ordonnancement[index2] = temp;
   }
}

void swap_sub_list(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   int num_swaps = nb_processes / 10;
   int start = i;
   int end = i + num_swaps;
   if (end > nb_processes)
   {
      end = nb_processes;
   }

   for (int j = 0; j < (end - start) / 2; j++)
   {
      int index1 = start + j;
      int index2 = end - 1 - j;
      int temp = ordonnancement[index1];
      ordonnancement[index1] = ordonnancement[index2];
      ordonnancement[index2] = temp;
   }
}

void swap_i_and_i_plus_1_three_times(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   for (int j = 0; j < 3; j++)
   {
      if (i + j + 1 < nb_processes)
      {
         int temp = ordonnancement[i + j];
         ordonnancement[i + j] = ordonnancement[i + j + 1];
         ordonnancement[i + j + 1] = temp;
      }
   }
}

void swap_i_and_i_plus_1_five_times(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   for (int j = 0; j < 3; j++)
   {
      if (i + j + 1 < nb_processes)
      {
         int temp = ordonnancement[i + j];
         ordonnancement[i + j] = ordonnancement[i + j + 1];
         ordonnancement[i + j + 1] = temp;
      }
   }
}