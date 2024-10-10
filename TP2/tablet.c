#include "tablet.h"

extern int memory_used;

/******************* Utils *******************/

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

void add_all_next_tablets(tablet_t tablet, tablet_t tablets[])
{
   add_all_next_tablets_i(tablet, tablets);
   add_all_next_tablets_j(tablet, &tablets[tablet.m - 1]);
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

void print_tablet(tablet_t tablet)
{
   for (int j = 0; j < tablet.n; j++)
   {
      for (int i = 0; i < tablet.m; i++)
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

tuple_t calculate_max_with_index(int configurations_res[], int n)
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

/******************* Basic recursive version *******************/

int calculate_configuration(tablet_t tablet)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets(tablet, tablets);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration(tablets[i]);
   }
   return calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
}

/******************* Dynamic version *******************/

int calculate_configuration_dynamic(tablet_t tablet, int16_t ****tab)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }
   int16_t array_value = tab[tablet.m - 1][tablet.n - 1][tablet.point.i][tablet.point.j];
   if (array_value != 0)
   {
      return array_value;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets(tablet, tablets);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_dynamic(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
   tab[tablet.m - 1][tablet.n - 1][tablet.point.i][tablet.point.j] = max;

   return max;
}

int calculate_configuration_dynamic_init(tablet_t tablet)
{
   int m = tablet.m - 1;
   int n = tablet.n - 1;
   int i = tablet.point.i + 1;
   int j = tablet.point.j + 1;

   int16_t ****array = init_array(m, n, i, j);
   int res = calculate_configuration_dynamic(tablet, array);
   free_array(array, m, n, i, j);
   return res;
}

/******************* Dynamic symetric version *******************/

tablet_t get_symetric_tablet_dimension(tablet_t tablet)
{
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

   i = MIN(i, m - 1 - i);
   j = MIN(j, n - 1 - j);
   return (tablet_t){m, n, {i, j}};
}

int calculate_configuration_dynamic_symetric(tablet_t tablet, int16_t ****tab)
{
   if (tablet.m == 1 && tablet.n == 1)
   {
      return 0;
   }

   tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);
   int16_t array_value = tab[symetric_dimensions.m - 1][symetric_dimensions.n - 1][symetric_dimensions.point.i][symetric_dimensions.point.j];
   if (array_value != 0)
   {
      return array_value;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets(tablet, tablets);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_dynamic_symetric(tablets[i], tab);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);
   tab[symetric_dimensions.m - 1][symetric_dimensions.n - 1][symetric_dimensions.point.i][symetric_dimensions.point.j] = max;
   return max;
}

int calculate_configuration_dynamic_init_symetric(tablet_t tablet)
{
   tablet_t symetric_dimensions = get_symetric_tablet_dimension(tablet);
   int m = symetric_dimensions.m - 1 / 2;
   int n = symetric_dimensions.n - 1 / 2;
   int i = symetric_dimensions.point.i + 1;
   int j = symetric_dimensions.point.j + 1;
   int16_t ****array = init_array(m, n, i, j);
   int res = calculate_configuration_dynamic_symetric(tablet, array);
   free_array(array, m, n, i, j);
   return res;
}

/******************* Hashmap version *******************/

int table_size = TABLE_3; // Change the hash depending on the tablet size.
                          // TABLE_1 for m and n < 25, TABLE_2 < 50, and TABLE_3 < 150
                          // it's more than that actually what matters also is the range between i and j in the tablet point

unsigned int hash_tablet(tablet_t tablet)
{
   int hash = (tablet.m * BASE_1 + tablet.n) % table_size;
   hash = (hash * BASE_2 + tablet.point.i) % table_size;
   hash = (hash * BASE_3 + tablet.point.j) % table_size;
   return hash;
}

int calculate_configuration_hash_init(tablet_t tablet)
{
   memory_used += sizeof(node_t *) * (table_size);
   node_t *hashmap[table_size + 1];
   memset(hashmap, 0, (table_size) * sizeof(node_t *));
   int res = calculate_configuration_hash(tablet, hashmap);
   for (int i = 0; i < table_size; i++)
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
   unsigned int hash = hash_tablet(symetric_dimensions);
   node_t *linked_list = hashmap[hash];
   while (linked_list != NULL)
   {
      if (linked_list->point.i == symetric_dimensions.point.i && linked_list->point.j == symetric_dimensions.point.j)
      {
         return linked_list->v;
      }
      linked_list = linked_list->next;
   }

   tablet_t tablets[tablet.m + tablet.n - 1];
   add_all_next_tablets(tablet, tablets);

   int configurations_res[tablet.m + tablet.n - 1];
   for (int i = 0; i < tablet.m - 1 + tablet.n - 1; i++) // plus clair que -2 directement
   {
      configurations_res[i] = calculate_configuration_hash(tablets[i], hashmap);
   }
   int max = calculate_max(configurations_res, tablet.m - 1 + tablet.n - 1);

   if (hashmap[hash] == NULL)
   {
      node_t *new_list = malloc(sizeof(node_t));
      new_list->point.i = symetric_dimensions.point.i;
      new_list->point.j = symetric_dimensions.point.j;
      new_list->v = max;
      new_list->next = NULL;
      hashmap[hash] = new_list;
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
      new_first->next = hashmap[hash];
      hashmap[hash] = new_first;
   }
   return max;
}

/******************* Game *******************/

void game(tablet_t tablet)
{
   int player = 1;
   int m, n, i, j;
   char played = 0;
   while (tablet.m > 1 || tablet.n > 1)
   {
      if (player == 1)
      {
         char c;
         int i;
         printf("Enter h (horizontal) or v (vertical) and a number\n");
         scanf("%c %d", &c, &i);
         if (c == 'h')
         {
            if (i < tablet.m)
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
               played = 1;
            }
            else
            {
               played = 0;
            }
         }
         else if (c == 'v')
         {
            if (i < tablet.n)
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
               played = 1;
            }
            else
            {
               played = 0;
            }
         }
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
         tuple_t max_index = calculate_max_with_index(configurations_res, tablet.m - 1 + tablet.n - 1);
         tablet = tablets[max_index.i];
         array[symetric_dimensions.m][symetric_dimensions.n][symetric_dimensions.point.i][symetric_dimensions.point.j] = max_index.j;
         played = 1;
         free_array(array, symetric_dimensions.m, symetric_dimensions.n, symetric_dimensions.point.i + 1, symetric_dimensions.point.j + 1);
      }
      if (played)
      {
         player = -player;
         printf("The value of the played configuration is %d\n", calculate_configuration_dynamic_init_symetric(tablet));
         printf("The tablet dimensions are now (%d, %d), (%d, %d)\n\n", tablet.m, tablet.n, tablet.point.i, tablet.point.j);
         print_tablet(tablet);
      }
      else
      {
         printf("Please enter a valid input\n");
      }
   }
}