#include "swap.h"

void swap(int *x, int *y)
{
   int temp = *x;
   *x = *y;
   *y = temp;
}

void swap_symetric(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes - 1 - i]] = i; // 240K
   ordonnancement[sorted_ordonnancement[i]] = nb_processes - 1 - i;
}

void swap_i_and_middle(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes / 2]] = i; // 218K
   ordonnancement[sorted_ordonnancement[i]] = nb_processes / 2;
}

void swap_i_and_i_plus_nb_processes_div_2(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[(nb_processes + (nb_processes / 2)) % nb_processes]] = i; // 218k
   ordonnancement[sorted_ordonnancement[i]] = (nb_processes + (nb_processes / 2)) % nb_processes;
}

void swap_i_and_i_plus_1(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i)
{
   ordonnancement[sorted_ordonnancement[nb_processes - 1]] = i; // 201K
   ordonnancement[sorted_ordonnancement[i]] = nb_processes - 1;
}