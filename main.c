#include "ex2.h"

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