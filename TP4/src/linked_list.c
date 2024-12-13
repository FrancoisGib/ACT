#include "linked_list.h"

ll_node_t *add_element(ll_node_t *node, int *ordonnancement, int nb_processes, int delay)
{
    ll_node_t *new_node = malloc(sizeof(ll_node_t));
    new_node->ordonnancement = malloc(nb_processes * sizeof(int));
    memcpy(new_node->ordonnancement, ordonnancement, nb_processes * sizeof(int));
    new_node->delay = delay;
    new_node->next = node;
    return new_node;
}

void free_list(ll_node_t *root)
{
    ll_node_t *node = root;
    while ((node = root) != NULL)
    {
        root = root->next;
        free(node->ordonnancement);
        free(node);
    }
}