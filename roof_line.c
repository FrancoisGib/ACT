#include "roof_line.h"

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
   printf("\n");
}

roof_line_t *construct_line(int triplets[][3], int n)
{
   roof_line_t *roof_line = (roof_line_t *)malloc(sizeof(roof_line_t));
   if (n == 1)
   {
      node_t *first_point = (node_t *)malloc(sizeof(node_t));
      first_point->x = triplets[0][0];
      first_point->y = triplets[0][1];
      node_t *second_point = (node_t *)malloc(sizeof(node_t));
      second_point->x = triplets[0][2];
      second_point->y = 0;
      roof_line->root = first_point;
      first_point->next = second_point;
      return roof_line;
   }
   else
   {
      int size = n / 2;
      roof_line_t *left = construct_line(triplets, size);
      roof_line_t *right = construct_line(&triplets[size], n - size);
      roof_line_t *merged = fusion(left, right);
      return merged;
   }
}

roof_line_t *fusion(roof_line_t *first_line, roof_line_t *second_line)
{
   roof_line_t *roof_line = (roof_line_t *)malloc(sizeof(roof_line_t));
   node_t *fl_point = first_line->root;
   node_t *sl_point = second_line->root;

   int x1, x2, y1, y2;

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
      node = malloc(sizeof(node_t));

      if (x1 < x2)
      {
         node->x = x1;
         h1 = y1;
         fl_point = fl_point->next;
      }
      else if (x1 > x2)
      {
         node->x = x2;
         h2 = y2;
         sl_point = sl_point->next;
      }
      else
      {
         node->x = x1;
         h1 = y1;
         h2 = y2;
         fl_point = fl_point->next;
         sl_point = sl_point->next;
      }
      node->y = MAX(h1, h2);

      if (current == NULL)
      {
         current = node;
         roof_line->root = current;
      }
      else
      {
         if (current->y != node->y)
         {
            current->next = node;
            current = current->next;
         }
         else // if the point before has the same y (example: (3,7) and (5,7), we juste keep the (3,7)), so we free the new node
         {
            free(node);
         }
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

   free_roof_line(first_line);
   free_roof_line(second_line);
   return roof_line;
}

roof_line_t *decompress_line(roof_line_t *line)
{
   roof_line_t *svg = malloc(sizeof(roof_line_t));
   node_t *node;
   node_t *current = line->root;
   node_t *svg_current;
   int pair = 0;
   node = malloc(sizeof(node_t));
   node->x = current->x;
   node->y = 0;
   svg->root = node;
   svg_current = node;
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

   FILE *file = fopen(filename, "w");
   fwrite(header, strlen(header), 1, file);
   fwrite(buffer, buf_length, 1, file);
   fwrite(footer, strlen(footer), 1, file);
   fclose(file);

   free_roof_line(decompressed_line);
}
