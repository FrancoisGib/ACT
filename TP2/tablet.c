#include "tablet.h"

int calculate_configuration(tablet_t current_tablet, int depth)
{
   // printf("(%d, %d), (%d, %d)\n", current_tablet.m, current_tablet.n, current_tablet.point.i, current_tablet.point.j);
   if (current_tablet.m == 1 && current_tablet.n == 1)
   {
      return 0;
   }
   tablet_t tablets[current_tablet.m + current_tablet.n - 1];
   set_horizontal_configurations(current_tablet, tablets);
   set_vertical_configurations(current_tablet, &tablets[current_tablet.m - 1]);

   int configurations_res[current_tablet.m + current_tablet.n - 1];
   for (int i = 0; i < current_tablet.m + current_tablet.n - 2; i++)
   {
      // printf("(%d, %d), (%d, %d)\n", tablets[i].m, tablets[i].n, tablets[i].point.i, tablets[i].point.j);
      configurations_res[i] = calculate_configuration(tablets[i], depth + 1);
   }
   int max = calculate_max(configurations_res, current_tablet.m + current_tablet.n - 2);
   if (max == 0)
   {
      max = depth + 1 % 2 == 0 ? 1 : -1;
   }
   else
   {
      max = ADD_ONE_AND_REVERSE(max);
   }
   return max;
}

int calculate_max(int configurations_res[], int n)
{
   int max = 0;
   for (int i = 0; i < n; i++)
   {
      printf("%d ", configurations_res[i]);
      if (max < 0)
      {
         if (configurations_res[i] < 0)
         {
            max = MAX(max, configurations_res[i]);
         }
      }
      else
      {
         if (configurations_res[i] < 0)
         {
            max = configurations_res[i];
         }
         else
         {
            max = MAX(max, configurations_res[i]);
         }
      }
   }
   printf("%d\n", max);
   return max;
}

void add_all_next_tablets_when_point_i_at_beginning(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.m; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = current_tablet.m - i;
      new_tablet.n = current_tablet.n;
      new_tablet.point.i = current_tablet.point.i;
      new_tablet.point.j = current_tablet.point.j;

      // printf("i (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_when_point_i_at_end(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.m; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = current_tablet.m - i;
      new_tablet.n = current_tablet.n;
      new_tablet.point.i = new_tablet.m - 1;
      new_tablet.point.j = current_tablet.point.j;

      // printf("i (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_when_point_i_inside(tablet_t current_tablet, tablet_t tablets[])
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

      // printf("i (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_when_point_j_at_beginning(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.n; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = current_tablet.m;
      new_tablet.n = current_tablet.n - i;
      new_tablet.point.i = current_tablet.point.i;
      new_tablet.point.j = current_tablet.point.j;

      // printf("jb (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_when_point_j_at_end(tablet_t current_tablet, tablet_t tablets[])
{
   for (int i = 1; i < current_tablet.n; i++)
   {
      tablet_t new_tablet;
      new_tablet.m = current_tablet.m;
      new_tablet.n = current_tablet.n - i;
      new_tablet.point.i = current_tablet.point.i;
      new_tablet.point.j = new_tablet.n - 1;

      // printf("je (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void add_all_next_tablets_when_point_j_inside(tablet_t current_tablet, tablet_t tablets[])
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

      // printf("ji (%d, %d), (%d, %d)\n", new_tablet.m, new_tablet.n, new_tablet.point.i, new_tablet.point.j);
      tablets[i - 1] = new_tablet;
   }
}

void set_horizontal_configurations(tablet_t current_tablet, tablet_t tablets[])
{
   if (current_tablet.point.i == 0)
   {
      add_all_next_tablets_when_point_i_at_beginning(current_tablet, tablets);
   }
   else if (current_tablet.point.i == current_tablet.m - 1)
   {
      add_all_next_tablets_when_point_i_at_end(current_tablet, tablets);
   }
   else
   {
      add_all_next_tablets_when_point_i_inside(current_tablet, tablets);
   }
}

void set_vertical_configurations(tablet_t current_tablet, tablet_t tablets[])
{
   if (current_tablet.point.j == 0)
   {
      add_all_next_tablets_when_point_j_at_beginning(current_tablet, tablets);
   }
   else if (current_tablet.point.j == current_tablet.n - 1)
   {
      add_all_next_tablets_when_point_j_at_end(current_tablet, tablets);
   }
   else
   {
      add_all_next_tablets_when_point_j_inside(current_tablet, tablets);
   }
}

int main()
{
   tablet_t tablet;
   tablet.m = 3;
   tablet.n = 1;
   point_t point = {0, 0};
   tablet.point = point;

   int res = calculate_configuration(tablet, 0);
   printf("res: %d\n", res);
   return 0;
}
