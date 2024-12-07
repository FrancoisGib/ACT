#ifndef INCLUDE_SWAP_H
#define INCLUDE_SWAP_H

typedef void (*swap_function)(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);

void swap(int *x, int *y);
void swap_symetric(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_middle(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_nb_processes_div_2(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);
void swap_i_and_i_plus_1(int *ordonnancement, int *sorted_ordonnancement, int nb_processes, int i);

#endif // INCLUDE_SWAP_H