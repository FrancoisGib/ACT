#include <stdio.h>
#include "lib.h"

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

typedef struct
{
    tablet_t tablet;
    int v;
} move_t;

int calculate_max(int configurations_res[], int n);
void add_all_next_tablets_i(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_j(tablet_t current_tablet, tablet_t tablets[]);
int calculate_configuration(tablet_t tablet);
int calculate_configuration_dynamic(tablet_t tablet, int16_t ****tab);
int calculate_configuration_dynamic_init(tablet_t tablet);
void calculate_all_configurations_equals_x(tablet_t tablet, int x);
int calculate_configuration_dynamic_symetric(tablet_t tablet, int16_t ****tab);
int calculate_configuration_dynamic_init_symetric(tablet_t tablet);
