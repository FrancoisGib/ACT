#ifndef INCLUDE_QUICKSORT_H
#define INCLUDE_QUICKSORT_H

#include <string.h>
#include "process.h"

typedef double (*value_function)(process_t *);
void quicksort(process_t *arr, int low, int high, value_function func);

#endif // INCLUDE_QUICKSORT_H