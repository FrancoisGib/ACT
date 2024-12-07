#ifndef INCLUDE_PROCESS_H
#define INCLUDE_PROCESS_H

typedef struct
{
    int time;
    int weight;
    int limit_time;
} process_t;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "quicksort.h"
#include "swap.h"
#include "lib.h"

#define MAX(x, y) (x) > (y) ? (x) : (y)

int sum_total_delay(process_t *processes, int nb_processes, int *ordonnancement);
void generate_random_solution(int *ordonnancement, int nb_processes);
int *constructive_heuristique(process_t *processes, int nb_processes);
int *hill_climbing(int *current_ordonnancement, process_t *processes, int nb_processes);
int *vnd(int *initial_ordonnancement, process_t *processes, int nb_processes, int k);

#endif // INCLUDE_PROCESS_H