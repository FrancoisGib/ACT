#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(x, y) (x) > (y) ? (x) : (y)

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

roof_line_t *construct_line(int triplets[][3], int n);
void print_roof_line(roof_line_t *roof_line);
void free_roof_line(roof_line_t *roof_line);
roof_line_t *fusion(roof_line_t *first_line, roof_line_t *second_line);
roof_line_t *decompress_line(roof_line_t *line);
void generate_svg_file(char *filename, int triplets[][3], int n);
roof_line_t *create_roof_line_with_points(int tuples[][2], int n);
int equals_lines(roof_line_t *first_line, roof_line_t *second_line);
int get_line_size(roof_line_t *roof_line);
