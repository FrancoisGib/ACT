#include "tablet.h"

int calculate_max(int configurations_res[], int n)
{
   int max = configurations_res[0];
   for (int i = 0; i < n; i++)
   {
      if (max <= 0)
      {
         if (configurations_res[i] <= 0)
         {
            max = MAX(max, configurations_res[i]);
         }
      }
      else
      {
         if (configurations_res[i] <= 0)
         {
            max = configurations_res[i];
         }
         else
         {
            max = MAX(max, configurations_res[i]);
         }
      }
   }

   if (max <= 0)
   {
      max = 1 - max;
   }
   else
   {
      max = -(1 + max);
   }

   return max;
}

void add_all_next_tablets_i(tablet_t tablet, tablet_t tablets[])
{
   for (int i = 1; i < tablet.m; i++)
   {
      tablet_t new_tablet;
      new_tablet.n = tablet.n;
      if (i <= tablet.point.i)
      {
         new_tablet.m = tablet.m - i;
         new_tablet.point.i = tablet.point.i - i;
      }
      else
      {
         new_tablet.m = i;
         new_tablet.point.i = tablet.point.i;
      }
      new_tablet.point.j = tablet.point.j;
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_j(tablet_t tablet, tablet_t tablets[])
{
   for (int i = 1; i < tablet.n; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = tablet.m;
      if (i <= tablet.point.j)
      {
         new_tablet.n = tablet.n - i;
         new_tablet.point.j = tablet.point.j - i;
      }
      else
      {
         new_tablet.n = i;
         new_tablet.point.j = tablet.point.j;
      }
      new_tablet.point.i = tablet.point.i;
      tablets[i - 1] = new_tablet;
   }
}

int calculate_configuration(tablet_t tablet)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }
   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets_i(tablet, tablets);
   add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration(tablets[i]);
   }
   return calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
}

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

int calculate_configuration_dynamic(tablet_t tablet, int16_t ****tab)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }

   int16_t array_value = tab[tablet.m][tablet.n][tablet.point.i][tablet.point.j];
   if (array_value != 0)
   {
      return array_value;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets_i(tablet, tablets);
   add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_dynamic(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
   tab[tablet.m][tablet.n][tablet.point.i][tablet.point.j] = max;
   return max;
}

int calculate_configuration_dynamic_init(tablet_t tablet)
{
   int m, n, i, j;
   m = tablet.m;
   n = tablet.n;
   i = tablet.point.i;
   j = tablet.point.j;

   int16_t ****array = init_array(m, n, i, j);
   int res = calculate_configuration_dynamic(tablet, array);
   free_array(array, m, n, i, j);
   return res;
}

void calculate_all_configurations_equals_x(tablet_t tablet, int x)
{
   int m, n, i, j;
   m = tablet.m;
   n = tablet.n;

   int16_t ****array = init_array(m, n, i, j);
   int res;
   for (int i = 0; i < tablet.m / 2 + 1; i++)
   {
      tablet.point.i = i;
      tablet.point.j = j;
      res = calculate_configuration_dynamic(tablet, array);
      if (res == x)
      {
         printf("(%d, %d), (%d, %d)\n", m, n, i, j);
         printf("(%d, %d), (%d, %d)\n", m, n, j, i);
      }

      tablet.point.i = m - i - 1;
      tablet.point.j = n - j - 1;
      res = calculate_configuration_dynamic(tablet, array);
      if (res == x)
      {
         printf("(%d, %d), (%d, %d)\n", m, n, m - i - 1, n - j - 1);
         printf("(%d, %d), (%d, %d)\n", m, n, n - j - 1, m - i - 1);
      }
   }
   free_array(array, m, n, i, j);
}

int calculate_configuration_dynamic_symetric(tablet_t tablet, int16_t ****tab)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }
   int m, n, i, j;
   if (tablet.m < tablet.n)
   {
      i = tablet.point.j;
      j = tablet.point.i;
      m = tablet.n;
      n = tablet.m;
   }
   else
   {
      i = tablet.point.i;
      j = tablet.point.j;
      m = tablet.m;
      n = tablet.n;
   }

   int16_t array_value = tab[m][n][i][j];
   if (array_value != 0)
   {
      return array_value;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets_i(tablet, tablets);
   add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_dynamic_symetric(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
   tab[m][n][i][j] = max;
   return max;
}

int calculate_configuration_dynamic_init_symetric(tablet_t tablet)
{
   int m, n, i, j;
   m = tablet.m;
   n = tablet.n;
   i = tablet.point.i;
   j = tablet.point.j;

   int16_t ****array = init_array(m + 1, n + 1, tablet.point.i + 1, tablet.point.j + 1);
   int res = calculate_configuration_dynamic_symetric(tablet, array);
   free_array(array, m + 1, n + 1, tablet.point.i + 1, tablet.point.j + 1);
   return res;
}

int main()
{
   tablet_t tablet;
   tablet.m = 100;
   tablet.n = 100;
   tablet.point.i = 80;
   tablet.point.j = 80;
   int res;
   clock_t start, end;
   double cpu_time_used;
   /*
   start = clock();
   res = calculate_configuration(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("res : %d, cpu time : %lf\n", res, cpu_time_used);
   */
   start = clock();
   res = calculate_configuration_dynamic_init(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("res : %d, cpu time : %lf\n", res, cpu_time_used);
   // calculate_all_configurations_equals_x(tablet, 191);

   start = clock();
   res = calculate_configuration_dynamic_init_symetric(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("res : %d, cpu time : %lf\n", res, cpu_time_used);
   return 0;
}
