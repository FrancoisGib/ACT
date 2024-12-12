#ifndef INCLUDE_QUICKSORT_H
#define INCLUDE_QUICKSORT_H

#include <string.h>
#include "process.h"

typedef double (*value_function)(process_t *);
void quicksort(process_t *arr, int low, int high, value_function func);
double limit_time_value_function(process_t *process);
double weight_over_time_value_function(process_t *process);
double sum_delay_value_function(process_t *process);
double weight_times_1_over_limit(process_t *process);

#endif // INCLUDE_QUICKSORT_H