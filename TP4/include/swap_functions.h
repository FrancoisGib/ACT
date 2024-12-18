#ifndef INCLUDE_SWAP_H
#define INCLUDE_SWAP_H

#include <stdlib.h>

typedef void (*swap_function)(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);

void swap(int *x, int *y);
void swap_symetric(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_middle(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_nb_processes_div_2(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_1(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_random(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void shift_left(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void shift_right(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_sub_list_nb_processes_per_4(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_random_nb_processes_per_4(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void shift_left_lasts_i(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_sub_list(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_1_three_times(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_1_five_times(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);

#endif // INCLUDE_SWAP_H