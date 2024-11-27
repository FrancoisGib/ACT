#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "quicksort.h"

#define MAX(x, y) (x) > (y) ? (x) : (y)

typedef struct
{
    int nb_processes;
    process_t *processes;
} process_file_t;

int sum_total_delay(process_t *processes, int nb_processes, int *ordonnancement);
void generate_random_solution(int *ordonnancement, int nb_processes);
process_file_t *parse_file(char *path);