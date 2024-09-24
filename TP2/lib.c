#include "lib.h"

int16_t ****init_array(int m, int n, int i, int j)
{
   int16_t ****tab = malloc((m + 1) * sizeof(int16_t ***)); // int16_t for less memory (16 bits is enough)
   for (int i = 0; i <= m; i++)
   {
      tab[i] = malloc((n + 1) * sizeof(int16_t **));
      for (int j = 0; j <= n; j++)
      {
         tab[i][j] = malloc((i + 1) * sizeof(int16_t *));
         for (int k = 0; k <= i; k++)
         {
            tab[i][j][k] = malloc((j + 1) * sizeof(int16_t));
            for (int l = 0; l <= j; l++)
            {
               tab[i][j][k][l] = 0;
            }
         }
      }
   }
   return tab;
}

void free_array(int16_t ****array, int m, int n, int i, int j)
{
   for (int i = 0; i <= m; i++)
   {
      for (int j = 0; j <= n; j++)
      {
         for (int k = 0; k <= i; k++)
         {
            free(array[i][j][k]);
         }
         free(array[i][j]);
      }
      free(array[i]);
   }
   free(array);
}