#include "lib.h"

int16_t ****init_array(int m, int n, int i, int j)
{
   int16_t ****tab = malloc((m + 1) * sizeof(int16_t ***)); // int16_t for less memory (16 bits is enough)
   for (int x = 0; x <= m; x++)
   {
      tab[x] = malloc((n + 1) * sizeof(int16_t **));
      for (int y = 0; y <= n; y++)
      {
         tab[x][y] = malloc((i + 1) * sizeof(int16_t *));
         for (int k = 0; k <= i; k++)
         {
            tab[x][y][k] = malloc((j + 1) * sizeof(int16_t));
            for (int l = 0; l <= j; l++)
            {
               tab[x][y][k][l] = 0;
            }
         }
      }
   }
   return tab;
}

void free_array(int16_t ****array, int m, int n, int i, int j)
{
   for (int x = 0; x <= m; x++)
   {
      for (int y = 0; y <= n; y++)
      {
         for (int k = 0; k <= i; k++)
         {
            free(array[x][y][k]);
         }
         free(array[x][y]);
      }
      free(array[x]);
   }
   free(array);
}