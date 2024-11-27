#include "quicksort.h"

void swap(process_t *a, process_t *b)
{
    process_t temp = *a;
    a->limit_time = b->limit_time;
    a->time = b->time;
    a->weight = b->weight;
    b->limit_time = temp.limit_time;
    b->time = temp.time;
    b->weight = temp.weight;
}

int partition(process_t *arr, int low, int high, value_function func)
{

    int p = func(&arr[low]);
    int i = low;
    int j = high;

    while (i < j)
    {
        while (func(&arr[i]) <= p && i <= high - 1)
        {
            i++;
        }
        while (func(&arr[j]) > p && j >= low + 1)
        {
            j--;
        }
        if (i < j)
        {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quicksort(process_t *arr, int low, int high, value_function func)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, func);
        quicksort(arr, low, pi - 1, func);
        quicksort(arr, pi + 1, high, func);
    }
}
