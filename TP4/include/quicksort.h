#include <string.h>

typedef struct
{
    int time;
    int weight;
    int limit_time;
} process_t;

typedef int (*value_function)(process_t *);
void swap(process_t *a, process_t *b);
int partition(process_t *arr, int low, int high, value_function func);
void quicksort(process_t *arr, int low, int high, value_function func);