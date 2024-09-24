#include <inttypes.h>
#include <stdlib.h>

struct move_pair_s
{
   int i;
   int v;
};
typedef struct move_pair_s move_pair_t;

int16_t ****init_array(int m, int n, int i, int j);
void free_array(int16_t ****array, int m, int n, int i, int j);