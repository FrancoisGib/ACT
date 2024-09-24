#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>

#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) > (y) ? (y) : (x)

typedef struct
{
    int i;
    int j;
} point_t;

typedef struct
{
    int m;
    int n;
    point_t point;
} tablet_t;

int calculate_max(int configurations_res[], int n);
void add_all_next_tablets_i(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_j(tablet_t current_tablet, tablet_t tablets[]);
