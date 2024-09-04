#include <stdlib.h>
#include <stdio.h>

typedef struct node_s
{
   int x;
   int y;
   struct node_s *next;
} node_t;

typedef struct
{
   node_t *root;
} roof_line_t;

void free_roof_line(roof_line_t *roof_line)
{
   node_t *node = roof_line->root;
   node_t *next_node;
   while (node != NULL)
   {
      next_node = node->next;
      free(node);
      node = next_node;
   }
}

void print_roof_line(roof_line_t *roof_line)
{
   node_t *node = roof_line->root;
   while (node != NULL)
   {
      printf("(%d, %d) ", node->x, node->y);
      node = node->next;
   }
}

void add_point(roof_line_t *roof_line, int triplet[3])
{
   int x1 = triplet[0];
   int y1 = triplet[1];
   int x2 = triplet[2];
   node_t *first_point = (node_t *)malloc(sizeof(node_t));
   first_point->x = x1;
   first_point->y = y1;

   if (roof_line->root == NULL) // cas tableau vide
   {
      roof_line->root = first_point;
      node_t *second_point = (node_t *)malloc(sizeof(node_t));
      second_point->x = x2;
      second_point->y = 0;
      first_point->next = second_point;
      return;
   }

   // cas tableau non vide
   node_t *temp = roof_line->root;
   if (x1 < temp->x) // ajout au début
   {
      first_point->next = temp;
      roof_line->root = first_point;
   }

   // ajout du second à la fin
   while (x1 > temp->x)
   {
      if (temp->next == NULL) // ajout à la fin
      {
         temp->next = first_point;
         node_t *second_point = (node_t *)malloc(sizeof(node_t));
         second_point->x = x2;
         second_point->y = 0;
         first_point->next = second_point;
      }
      else // ajout dedans
      {
         if (temp->next->x > x1) // insertion au milieu
         {
            first_point->next = temp->next;
            temp->next = first_point;
            if (x2 > first_point->next->next->x) // si on a un chevauchement
            {
               first_point->next->next->y = y1;
               node_t *second_point = (node_t *)malloc(sizeof(node_t));
               second_point->x = x2;
               second_point->y = 0;
               first_point->next->next->next = second_point;
            }
         }
      }
      temp = temp->next;
   }
}

roof_line_t *create_roof_line(int data[][3], int n)
{
   roof_line_t *roof_line = (roof_line_t *)malloc(sizeof(roof_line_t));
   for (int i = 0; i < n; i++)
   {
      add_point(roof_line, data[i]);
   }
   return roof_line;
}

int main()
{

   int data[][3] = {
       {3, 13, 9},
       {1, 11, 5},
       {19, 18, 22},
       {3, 6, 7},
       {16, 3, 25},
       {12, 7, 16}};

   roof_line_t *line = create_roof_line(data, sizeof(data) / (sizeof(data[0])));
   print_roof_line(line);
   free_roof_line(line);
   return 0;
}