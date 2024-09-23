#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) (x) > (y) ? (x) : (y)

#define ADD_ONE_AND_REVERSE(x) (x) >= 0 ? -(1 + (x)) : 1 - (x)

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
void add_all_next_tablets_when_point_i_at_beginning(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_when_point_i_at_end(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_when_point_i_inside(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_when_point_j_at_beginning(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_when_point_j_at_end(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_when_point_j_inside(tablet_t current_tablet, tablet_t tablets[]);
void set_horizontal_configurations(tablet_t current_tablet, tablet_t tablets[]);
void set_vertical_configurations(tablet_t current_tablet, tablet_t tablets[]);
