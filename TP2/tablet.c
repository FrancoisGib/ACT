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

int main()
{
   tablet_t tablet;
   tablet.m = 3;
   tablet.n = 2;
   point_t point = {2, 0};
   tablet.point = point;

   int res = calculate_configuration(tablet);
   printf("res : %d\n", res);
   /*int test1[] = {2, 4, 11, 0};
   int res1 = calculate_max(test1, sizeof(test1) / sizeof(int), 1);
   printf("res: %d\n", res1);

   int test2[] = {-11, 3, -8, 17};
   int res2 = calculate_max(test2, sizeof(test2) / sizeof(int), 1);
   printf("res: %d\n", res2);*/
   return 0;
}
