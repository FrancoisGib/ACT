#include "ex2.h"

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
      add_point2(roof_line, data[i]);
   }
   return roof_line;
}

void add_point2(roof_line_t *roof_line, int triplet[3]) 
{
    int x1 = triplet[0];
    int y1 = triplet[1];
    int x2 = triplet[2];
    node_t *first_point = (node_t *)malloc(sizeof(node_t));
    first_point->x = x1;
    first_point->y = y1;

    if (roof_line->root == NULL) 
    {
        roof_line->root = first_point;

        node_t *second_point = (node_t *)malloc(sizeof(node_t));
        second_point->x = x2;
        second_point->y = 0;
        first_point->next = second_point;
        return;
    }

    node_t *current = roof_line->root;
    while (x1 > current->x) {
        if (current->next == NULL) {
            current->next = first_point;
            node_t *second_point = (node_t *)malloc(sizeof(node_t));
            second_point->x = x2;
            second_point->y = 0;
            first_point->next = second_point;
            return;
        }
        current = current->next;
    }

    if (x1 == current->x) {
        current->x = x1 > current->x ? x1 : current->x;
    }
    else {
        first_point->next = current->next;
        current->next = first_point;
        first_point->next->y = y1;
    }

    current = first_point;
    /*while (x2 > current->next->x && current->next != NULL) {
        current->next = current->next->next;
    }*/
    node_t *second_point = (node_t *)malloc(sizeof(node_t));
    second_point->x = x2;
    second_point->y = 0;
    first_point->next = second_point;
}




roof_line_t *fusion(roof_line_t *first_line, roof_line_t *second_line) 
{
    return NULL;
}

roof_line_t *construct_line(int triplets[][3], int n) {
    roof_line_t * roof_line = (roof_line_t*)malloc(sizeof(roof_line_t));
    if (n == 1) {
        add_point(roof_line, triplets[0]);
    }
    else {
        int size = n / 2;
        roof_line_t *left = construct_line(triplets, size);
        roof_line_t *right = construct_line(&triplets[size], n - size);
        return fusion(left, right);
    }
    return roof_line;
}