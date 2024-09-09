#include "roof_line.h"

void free_roof_line(roof_line_t *roof_line)
{
   node_t *node;
   node_t *next_node = roof_line->root;
   while ((node = next_node) != NULL)
   {
      next_node = node->next;
      free(node);
   }
   free(roof_line);
}

void print_roof_line(roof_line_t *roof_line)
{
   node_t *node = roof_line->root;
   while (node != NULL)
   {
      printf("(%d, %d) ", node->x, node->y);
      node = node->next;
   }
   printf("\n");
}

roof_line_t *construct_line(int triplets[][3], int n)
{
   if (n == 1)
   {
      roof_line_t *roof_line = (roof_line_t *)malloc(sizeof(roof_line_t));
      node_t *first_point = malloc(sizeof(node_t));
      first_point->x = triplets[0][0];
      first_point->y = triplets[0][1];
      node_t *second_point = malloc(sizeof(node_t));
      second_point->x = triplets[0][2];
      second_point->y = 0;
      second_point->next = NULL;
      first_point->next = second_point;
      roof_line->root = first_point;
      return roof_line;
   }
   else
   {
      int size = n / 2;
      roof_line_t *left = construct_line(triplets, size);
      roof_line_t *right = construct_line(&triplets[size], n - size);
      roof_line_t *merged = fusion(left, right);
      free_roof_line(left);
      free_roof_line(right);
      return merged;
   }
}

roof_line_t *create_roof_line_with_points(int tuples[][2], int n)
{
   roof_line_t *roof_line = malloc(sizeof(roof_line));
   node_t *node;
   node_t *current = NULL;
   for (int i = 0; i < n; i++)
   {
      node_t *node = malloc(sizeof(node_t));
      node->x = tuples[i][0];
      node->y = tuples[i][1];
      if (current == NULL)
      {
         current = node;
         roof_line->root = current;
      }
      else
      {
         current->next = node;
         current = current->next;
      }
   }
   current->next = NULL; // can cause memory error if we don't initialize the last node's next to NULL
   return roof_line;
}

int equals_lines(roof_line_t *first_line, roof_line_t *second_line)
{
   node_t *fl_point = first_line->root;
   node_t *sl_point = second_line->root;
   while (fl_point != NULL && sl_point != NULL)
   {
      if (!(fl_point->x == sl_point->x && fl_point->y == sl_point->y))
      {
         return 0;
      }
      fl_point = fl_point->next;
      sl_point = sl_point->next;
   }
   return fl_point == NULL && sl_point == NULL;
}

roof_line_t *fusion(roof_line_t *first_line, roof_line_t *second_line)
{
   roof_line_t *roof_line = (roof_line_t *)malloc(sizeof(roof_line_t));
   node_t *fl_point = first_line->root;
   node_t *sl_point = second_line->root;

   int x1, x2, y1, y2, x, y;

   int h1 = 0;
   int h2 = 0;

   node_t *current = NULL;
   node_t *node;

   while (fl_point != NULL && sl_point != NULL)
   {
      x1 = fl_point->x;
      y1 = fl_point->y;
      x2 = sl_point->x;
      y2 = sl_point->y;

      if (x1 < x2)
      {
         x = x1;
         h1 = y1;
         fl_point = fl_point->next;
      }
      else if (x1 > x2)
      {
         x = x2;
         h2 = y2;
         sl_point = sl_point->next;
      }
      else
      {
         x = x1;
         h1 = y1;
         h2 = y2;
         fl_point = fl_point->next;
         sl_point = sl_point->next;
      }
      y = MAX(h1, h2);

      if (current == NULL)
      {
         node = malloc(sizeof(node_t));
         node->x = x;
         node->y = y;
         current = node;
         roof_line->root = current;
      }
      else
      {
         if (current->y != y)
         {
            node = malloc(sizeof(node_t));
            node->x = x;
            node->y = y;
            current->next = node;
            current = current->next;
         }
         // if the point before has the same y (example: (3,7) and (5,7),
         // we juste keep the (3,7)), so we don't need to add the new node
      }
   }

   while (sl_point != NULL)
   {
      node = malloc(sizeof(node_t));
      node->x = sl_point->x;
      node->y = sl_point->y;
      current->next = node;
      current = current->next;
      sl_point = sl_point->next;
   }
   while (fl_point != NULL)
   {
      node = malloc(sizeof(node_t));
      node->x = fl_point->x;
      node->y = fl_point->y;
      current->next = node;
      fl_point = fl_point->next;
      current = current->next;
   }
   current->next = NULL; // can cause memory error if the last node's next is not NULL
   return roof_line;
}

roof_line_t *decompress_line(roof_line_t *line)
{
   roof_line_t *svg = malloc(sizeof(roof_line_t));
   node_t *current = line->root;
   node_t *svg_current;
   int pair = 0;
   node_t *node;
   if (current != NULL)
   {
      node = malloc(sizeof(node_t));
      node->x = current->x;
      node->y = 0;
      svg->root = node;
      svg_current = node;
   }
   while (current != NULL)
   {
      node = malloc(sizeof(node_t));
      if (pair)
      {
         node->x = current->x;
         node->y = svg_current->y;
      }
      else
      {
         node->x = current->x;
         node->y = current->y;
         current = current->next;
      }
      pair = !pair;
      svg_current->next = node;
      svg_current = svg_current->next;
   }
   svg_current->next = NULL; // can cause memory error if the last node's next is not NULL
   return svg;
}

void generate_svg_file(char *filename, int triplets[][3], int n)
{
   roof_line_t *roof_line = construct_line(triplets, n);
   roof_line_t *decompressed_line = decompress_line(roof_line);
   free_roof_line(roof_line);

   char header[] = "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"600\" height=\"400\" viewBox=\"10 -200 200 200\"><polyline points=\"";
   char footer[] = "\" stroke=\"blue\" stroke-width=\"1\" fill=\"none\" transform=\"scale(1, -1)\"/></svg>";
   char buffer[1024];

   node_t *node = decompressed_line->root;
   int buf_length = 0;
   while (node != NULL)
   {
      char x[5];
      sprintf(x, "%d", node->x);
      strcpy(&buffer[buf_length], x);
      buf_length += strlen(x);

      buffer[buf_length] = ',';
      buf_length++;

      char y[5];
      sprintf(y, "%d", node->y);
      strcpy(&buffer[buf_length], y);
      buf_length += strlen(y);

      buffer[buf_length] = ' ';
      buf_length++;

      node = node->next;
   }
   free_roof_line(decompressed_line);

   FILE *file = fopen(filename, "w");
   fwrite(header, strlen(header), 1, file);
   fwrite(buffer, buf_length, 1, file);
   fwrite(footer, strlen(footer), 1, file);
   fclose(file);
}
