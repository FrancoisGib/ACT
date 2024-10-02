#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>

int16_t ****init_array(int m, int n, int i, int j);
void free_array(int16_t ****array, int m, int n, int i, int j);
void get_array_usage(int16_t ****array, int m, int n, int i, int j);
void print_array(int16_t ****array, int m, int n, int i, int j);