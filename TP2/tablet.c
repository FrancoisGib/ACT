#include "tablet.h"

extern int memory_used;

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

   int16_t ****array = init_array(m, n, i + 1, j + 1);
   int res = calculate_configuration_dynamic(tablet, array);
   free_array(array, m, n, i + 1, j + 1);
   return res;
}

void calculate_all_configurations_equals_x(tablet_t tablet, int x)
{
   int m, n, i, j;
   m = tablet.m;
   n = tablet.n;
   i = tablet.m;
   j = tablet.n;

   int16_t ****array = init_array(m, n, i, j);
   int res;
   for (int i = 0; i < tablet.m / 2 + 1; i++)
   {
      tablet.point.i = i;
      tablet.point.j = j;
      res = calculate_configuration_dynamic_symetric(tablet, array);
      if (res == x)
      {
         printf("(%d, %d), (%d, %d)\n", m, n, i, j);
         printf("(%d, %d), (%d, %d)\n", m, n, j, i);
      }

      tablet.point.i = m - i - 1;
      tablet.point.j = n - j - 1;
      res = calculate_configuration_dynamic_symetric(tablet, array);
      if (res == x)
      {
         printf("(%d, %d), (%d, %d)\n", m, n, m - i - 1, n - j - 1);
         printf("(%d, %d), (%d, %d)\n", m, n, n - j - 1, m - i - 1);
      }
   }
   free_array(array, m, n, i, j);
}

tablet_t get_symetric_tablet_dimension(tablet_t tablet)
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

   i = MIN(i, m - 1 - i);
   j = MIN(j, n - 1 - j);

   return (tablet_t){m, n, (point_t){i, j}};
}

int calculate_configuration_dynamic_symetric(tablet_t tablet, int16_t ****tab)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }

   tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);
   int16_t array_value = tab[symetric_dimensions.m][symetric_dimensions.n][symetric_dimensions.point.i][symetric_dimensions.point.j];
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
   tab[symetric_dimensions.m][symetric_dimensions.n][symetric_dimensions.point.i][symetric_dimensions.point.j] = max;
   return max;
}

int calculate_configuration_dynamic_init_symetric(tablet_t tablet)
{
   tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);
   int16_t ****array = init_array(symetric_dimensions.m, symetric_dimensions.n, symetric_dimensions.point.i + 1, symetric_dimensions.point.j + 1);
   int res = calculate_configuration_dynamic_symetric(tablet, array);
   free_array(array, symetric_dimensions.m, symetric_dimensions.n, symetric_dimensions.point.i + 1, symetric_dimensions.point.j + 1);
   return res;
}

tuple_t calculate_max_index(int configurations_res[], int n)
{
   int max = configurations_res[0];
   int index = 0;
   for (int i = 0; i < n; i++)
   {
      if (max <= 0)
      {
         if (configurations_res[i] <= 0)
         {
            if (max < configurations_res[i])
            {
               max = configurations_res[i];
               index = i;
            }
         }
      }
      else
      {
         if (configurations_res[i] <= 0)
         {
            max = configurations_res[i];
            index = i;
         }
         else
         {
            if (max < configurations_res[i])
            {
               max = configurations_res[i];
               index = i;
            }
         }
      }
   }

   return (tuple_t){index, max};
}

void game(tablet_t tablet)
{
   int player = 1;
   int m, n, i, j;

   while (tablet.m > 1 || tablet.n > 1)
   {
      if (player == 1)
      {
         char c;
         int i;
         printf("Enter h or v and a number\n");
         scanf("%c %d", &c, &i);
         if (c == 'h')
         {
            if (i <= tablet.point.i)
            {
               tablet.m = tablet.m - i;
               tablet.point.i = tablet.point.i - i;
            }
            else
            {
               tablet.m = i;
            }
         }
         else if (c == 'v')
         {
            if (i <= tablet.point.j)
            {
               tablet.n = tablet.n - i;
               tablet.point.j = tablet.point.j - i;
            }
            else
            {
               tablet.n = i;
            }
         }
         printf("La valeur de la configuration jouée est de %d\n", calculate_configuration_dynamic_init_symetric(tablet));
         player = -player;
      }

      else
      {
         tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);
         int16_t ****array = init_array(symetric_dimensions.m, symetric_dimensions.n, symetric_dimensions.point.i + 1, symetric_dimensions.point.j + 1);
         tablet_t tablets[tablet.m + tablet.n - 1];
         add_all_next_tablets_i(tablet, tablets);
         add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);

         int configurations_res[tablet.m + tablet.n - 1];
         for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
         {
            configurations_res[i] = calculate_configuration_dynamic_symetric(tablets[i], array);
         }
         tuple_t max_index = calculate_max_index(configurations_res, tablet.m - 1 + tablet.n - 1);
         tablet = tablets[max_index.i];
         array[symetric_dimensions.m][symetric_dimensions.n][symetric_dimensions.point.i][symetric_dimensions.point.j] = max_index.j;
         printf("La valeur de la configuration jouée est de %d\n", max_index.j);
         player = -player;
         free_array(array, symetric_dimensions.m, symetric_dimensions.n, symetric_dimensions.point.i + 1, symetric_dimensions.point.j + 1);
      }
      printf("Les dimensions de la tablette sont maintenant de (%d, %d), (%d, %d)\n\n", tablet.m, tablet.n, tablet.point.i, tablet.point.j);
      print_tablet(tablet);
   }
}

void print_tablet(tablet_t tablet)
{
   for (int i = 0; i < tablet.n; i++)
   {
      for (int j = 0; j < tablet.m; j++)
      {
         if (i == tablet.point.i && j == tablet.point.j)
         {
            printf("%s", " ☠️ ");
         }
         else
         {
            printf("%s", " ■ ");
         }
      }
      printf("\n");
   }
}

#define TABLE_1 4093
#define BASE_1 4091

#define TABLE_2 8191
#define BASE_2 8179

#define TABLE_3 16411
#define BASE_3 16381

#define TABLE_4 32771
#define BASE_4 32749

#define TABLE_5 65537
#define BASE_5 65521

#define TABLE_6 98317
#define BASE_6 98299

#define TABLE_SIZE TABLE_1
#define BASE BASE_1

unsigned long hash_tablet(int m, int n)
{
   return ((m * BASE) % TABLE_SIZE * BASE + n) % TABLE_SIZE;
}

int calculate_configuration_hash_init(tablet_t tablet)
{
   memory_used += sizeof(node_t *) * (TABLE_SIZE + 1);
   node_t *hashmap[TABLE_SIZE + 1];
   memset(hashmap, 0, (TABLE_SIZE + 1) * sizeof(node_t *));
   int res = calculate_configuration_hash(tablet, hashmap);
   for (int i = 0; i < TABLE_SIZE + 1; i++)
   {
      if (hashmap[i] != NULL)
      {
         node_t *linked_list = hashmap[i];
         node_t *temp;
         while (linked_list != NULL)
         {
            memory_used += sizeof(node_t);
            temp = linked_list->next;
            free(linked_list);
            linked_list = temp;
         }
      }
   }
   return res;
}

int calculate_configuration_hash(tablet_t tablet, node_t *hashmap[])
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }

   tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);

   node_t *linked_list = hashmap[hash_tablet(symetric_dimensions.m, symetric_dimensions.n)];
   while (linked_list != NULL)
   {
      if (linked_list->point.i == symetric_dimensions.point.i && linked_list->point.j == symetric_dimensions.point.j)
      {
         return linked_list->v;
      }
      linked_list = linked_list->next;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets_i(tablet, tablets);
   add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_hash(tablets[i], hashmap);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);

   if (hashmap[hash_tablet(symetric_dimensions.m, symetric_dimensions.n)] == NULL)
   {
      node_t *new_list = malloc(sizeof(node_t));
      new_list->point.i = symetric_dimensions.point.i;
      new_list->point.j = symetric_dimensions.point.j;
      new_list->v = max;
      new_list->next = NULL;
      hashmap[hash_tablet(symetric_dimensions.m, symetric_dimensions.n)] = new_list;
   }
   else
   {

      while (linked_list != NULL)
      {
         if (linked_list->point.i == symetric_dimensions.point.i && linked_list->point.j == symetric_dimensions.point.j)
         {
            return linked_list->v;
         }
         linked_list = linked_list->next;
      }
      node_t *new_first = malloc(sizeof(node_t));
      new_first->v = max;
      new_first->point.i = symetric_dimensions.point.i;
      new_first->point.j = symetric_dimensions.point.j;
      new_first->next = hashmap[hash_tablet(symetric_dimensions.m, symetric_dimensions.n)];
      hashmap[hash_tablet(symetric_dimensions.m, symetric_dimensions.n)] = new_first;
   }
   return max;
}
