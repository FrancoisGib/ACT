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

roof_line_t *create_roof_line(int data[][3], int n);
void add_point(roof_line_t *roof_line, int triplet[3]);
void add_point2(roof_line_t *roof_line, int triplet[3]);
void print_roof_line(roof_line_t *roof_line);
void free_roof_line(roof_line_t *roof_line);