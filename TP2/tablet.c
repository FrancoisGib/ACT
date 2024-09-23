#include "tablet.h"

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
   for (int i = 0; i < current_tablet.m + current_tablet.n - 2; i++)
   {
      configurations_res[i] = calculate_configuration(tablets[i]);
   }
   return calculate_max(configurations_res, current_tablet.m + current_tablet.n - 2);
}

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

int calculate_configuration_dynamic(tablet_t current_tablet, ll_point_t *tab[current_tablet.m][current_tablet.n])
{
   if (current_tablet.m == 1 && current_tablet.n == 1)
   {
      return 0;
   }
   ll_point_t *ll_point = tab[current_tablet.m][current_tablet.n];

   while (ll_point != NULL)
   {
      if (ll_point->point.i == current_tablet.point.i && ll_point->point.j == current_tablet.point.j)
      {
         return ll_point->value;
      }
      ll_point = ll_point->next;
   }
   tablet_t tablets[current_tablet.m + current_tablet.n - 1];
   add_all_next_tablets_i(current_tablet, tablets);
   add_all_next_tablets_j(current_tablet, &tablets[current_tablet.m - 1]);

   int configurations_res[current_tablet.m + current_tablet.n - 1];
   for (int i = 0; i < current_tablet.m + current_tablet.n - 2; i++)
   {
      configurations_res[i] = calculate_configuration_dynamic(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, current_tablet.m + current_tablet.n - 2);
   ll_point = tab[current_tablet.m][current_tablet.n];
   if (ll_point == NULL)
   {
      ll_point = malloc(sizeof(ll_point_t));
      ll_point->value = max;
      ll_point->point.i = current_tablet.point.i;
      ll_point->point.j = current_tablet.point.j;
      ll_point->next = NULL;
      tab[current_tablet.m][current_tablet.n] = ll_point;
   }
   else
   {
      ll_point_t *last_point;
      while (ll_point != NULL)
      {
         if (ll_point->point.i == current_tablet.point.i && ll_point->point.j == current_tablet.point.j)
         {
            ll_point->value = MAX(max, ll_point->value);
            return max;
         }
         last_point = ll_point;
         ll_point = ll_point->next;
      }
      last_point->next = malloc(sizeof(ll_point_t));
      last_point->value = max;
      last_point->point.i = current_tablet.point.i;
      last_point->point.j = current_tablet.point.j;
   }
   return max;
}

int calculate_configuration_dynamic_init(tablet_t current_tablet)
{
   ll_point_t *tab[current_tablet.m + 1][current_tablet.n + 1];
   for (int i = 0; i < current_tablet.m + 1; i++)
   {
      for (int j = 0; j < current_tablet.n + 1; j++)
      {
         tab[i][j] = NULL;
      }
   }
   return calculate_configuration_dynamic(current_tablet, tab);
}

int main()
{
   tablet_t tablet;
   tablet.m = 10;
   tablet.n = 7;
   point_t point = {2, 0};
   tablet.point = point;

   int res;

   clock_t start, end;
   double cpu_time_used;

   start = clock();
   res = calculate_configuration(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("res : %d, cpu time : %lf\n", res, cpu_time_used);

   start = clock();
   res = calculate_configuration_dynamic_init(tablet);
   end = clock();
   cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
   printf("res : %d, cpu time : %lf\n", res, cpu_time_used);
   /*int test1[] = {2, 4, 11, 0};
   int res1 = calculate_max(test1, sizeof(test1) / sizeof(int), 1);
   printf("res: %d\n", res1);

   int test2[] = {-11, 3, -8, 17};
   int res2 = calculate_max(test2, sizeof(test2) / sizeof(int), 1);
   printf("res: %d\n", res2);*/
   return 0;
}
