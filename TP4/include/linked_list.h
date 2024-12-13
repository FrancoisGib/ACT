#include "stdlib.h"
#include "string.h"

typedef struct ll_node_s
{
    struct ll_node_s *next;
    int delay;
    int *ordonnancement;
} ll_node_t;

ll_node_t *add_element(ll_node_t *node, int *ordonnancement, int nb_processes, int delay);
void free_list(ll_node_t *root);