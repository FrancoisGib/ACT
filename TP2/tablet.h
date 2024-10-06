#include "lib.h"

#define MAX(x, y) (x) > (y) ? (x) : (y)
#define MIN(x, y) (x) > (y) ? (y) : (x)

typedef struct
{
    int i;
    int j;
} point_t;

typedef point_t tuple_t;

typedef struct
{
    int m;
    int n;
    point_t point;
} tablet_t;

struct node_s
{
    int16_t v;
    point_t point;
    struct node_s *next;
};
typedef struct node_s node_t;

int calculate_max(int configurations_res[], int n);
tuple_t calculate_max_with_index(int configurations_res[], int n);

void add_all_next_tablets_i(tablet_t current_tablet, tablet_t tablets[]);
void add_all_next_tablets_j(tablet_t current_tablet, tablet_t tablets[]);

int calculate_configuration(tablet_t tablet);

int calculate_configuration_dynamic(tablet_t tablet, int16_t ****tab);
int calculate_configuration_dynamic_init(tablet_t tablet);

tablet_t get_symetric_tablet_dimension(tablet_t tablet);
int calculate_configuration_dynamic_symetric(tablet_t tablet, int16_t ****tab);
int calculate_configuration_dynamic_init_symetric(tablet_t tablet);

#define BASE_1 4091
#define BASE_2 16381
#define BASE_3 32759

#define TABLE_1 16411
#define TABLE_2 32771
#define TABLE_3 48131

int calculate_configuration_hash(tablet_t tablet, node_t *hashmap[]);
int calculate_configuration_hash_init(tablet_t tablet);

void print_tablet(tablet_t tablet);
void game(tablet_t tablet);