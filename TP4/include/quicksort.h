#include <string.h>

typedef struct
{
    int time;
    int weight;
    int limit_time;
} process_t;

typedef double (*value_function)(process_t *);
void quicksort(process_t *arr, int low, int high, value_function func);