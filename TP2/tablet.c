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

      i = MIN(i, tablet.n - 1 - i);
      j = MIN(j, tablet.m - 1 - j);
   }
   else
   {
      i = tablet.point.i;
      j = tablet.point.j;
      m = tablet.m;
      n = tablet.n;
   }

   i = MIN(i, m - 1 - i);
   j = MIN(j, n - 1 - j);

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
   if (tablet.m < tablet.n)
   {
      i = tablet.point.j;
      j = tablet.point.i;
      m = tablet.n;
      n = tablet.m;

      i = MIN(i, tablet.n - 1 - i);
      j = MIN(j, tablet.m - 1 - j);
   }
   else
   {
      i = tablet.point.i;
      j = tablet.point.j;
      m = tablet.m;
      n = tablet.n;
   }

   i = MIN(i, m - i);
   j = MIN(j, n - j);

   int16_t ****array = init_array(m, n, i, j);
   int res = calculate_configuration_dynamic_symetric(tablet, array);
   free_array(array, m, n, i, j);
   return res;
}