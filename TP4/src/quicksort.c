#include "quicksort.h"

void swap_processes(process_t *a, process_t *b)
{
    process_t temp = *a;
    *a = *b;
    *b = temp;
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
            swap_processes(&arr[i], &arr[j]);
        }
    }
    swap_processes(&arr[low], &arr[j]);
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
