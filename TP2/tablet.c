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

void add_all_next_tablets_i(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.m; i++)
   {
      tablet_t new_tablet;
      new_tablet.n = current_tablet.n;
      if (i <= current_tablet.point.i)
      {
         new_tablet.m = current_tablet.m - i;
         new_tablet.point.i = current_tablet.point.i - i;
      }
      else
      {
         new_tablet.m = i;
         new_tablet.point.i = current_tablet.point.i;
      }
      new_tablet.point.j = current_tablet.point.j;
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_j(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.n; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = current_tablet.m;
      if (i <= current_tablet.point.j)
      {
         new_tablet.n = current_tablet.n - i;
         new_tablet.point.j = current_tablet.point.j - i;
      }
      else
      {
         new_tablet.n = i;
         new_tablet.point.j = current_tablet.point.j;
      }
      new_tablet.point.i = current_tablet.point.i;
      tablets[i - 1] = new_tablet;
   }
}

int calculate_configuration(tablet_t current_tablet)
{
   if (current_tablet.m == 1 && current_tablet.n == 1)
   {
      return 0;
   }
   tablet_t tablets[current_tablet.m + current_tablet.n - 1];
   add_all_next_tablets_i(current_tablet, tablets);
   add_all_next_tablets_j(current_tablet, &tablets[current_tablet.m - 1]);

   int configurations_res[current_tablet.m + current_tablet.n - 1];
   for (int i = 0; i < current_tablet.m - 1 + current_tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration(tablets[i]);
   }
   return calculate_max(configurations_res, current_tablet.m - 1 + current_tablet.n - 1);
}

int calculate_configuration_dynamic(tablet_t current_tablet, int16_t ****tab)
{
   if (current_tablet.m == 1 && current_tablet.n == 1)
   {
      return 0;
   }

   int16_t array_value = tab[current_tablet.m][current_tablet.n][current_tablet.point.i][current_tablet.point.j];
   if (array_value != 0)
   {
      return array_value;
   }

   tablet_t tablets[current_tablet.m + current_tablet.n - 1];
   add_all_next_tablets_i(current_tablet, tablets);
   add_all_next_tablets_j(current_tablet, &tablets[current_tablet.m - 1]);

   int configurations_res[current_tablet.m + current_tablet.n - 1];
   for (int i = 0; i < current_tablet.m - 1 + current_tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_dynamic(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, current_tablet.m - 1 + current_tablet.n - 1);
   tab[current_tablet.m][current_tablet.n][current_tablet.point.i][current_tablet.point.j] = max;
   return max;
}

int calculate_configuration_dynamic_init(tablet_t current_tablet)
{
   int16_t ****tab = malloc((current_tablet.m + 1) * sizeof(int16_t ***)); // int16_t for less memory (16 bits is enough)
   for (int i = 0; i <= current_tablet.m; i++)
   {
      tab[i] = malloc((current_tablet.n + 1) * sizeof(int16_t **));
      for (int j = 0; j <= current_tablet.n; j++)
      {
         tab[i][j] = malloc((current_tablet.point.i + 1) * sizeof(int16_t *));
         for (int k = 0; k <= current_tablet.point.i; k++)
         {
            tab[i][j][k] = malloc((current_tablet.point.j + 1) * sizeof(int16_t));
            for (int l = 0; l <= current_tablet.point.j; l++)
            {
               tab[i][j][k][l] = 0;
            }
         }
      }
   }

   int res = calculate_configuration_dynamic(current_tablet, tab);

   for (int i = 0; i <= current_tablet.m; i++)
   {
      for (int j = 0; j <= current_tablet.n; j++)
      {
         for (int k = 0; k <= current_tablet.point.i; k++)
         {
            free(tab[i][j][k]);
         }
         free(tab[i][j]);
      }
      free(tab[i]);
   }
   free(tab);
   return res;
}

int main()
{
   tablet_t tablet;
   tablet.m = 100;
   tablet.n = 100;
   tablet.point.i = 48;
   tablet.point.j = 52;
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

   return 0;
}
