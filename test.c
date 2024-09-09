#include "roof_line.h"

static int test_number = 1;

roof_line_t *read_test_file(char *filename)
{
   FILE *file = fopen(filename, "r");
   int size;
   fscanf(file, "%d\n", &size);
   int triplets[size][3];
   int x1, y, x2;
   for (int i = 0; i < size; i++)
   {
      fscanf(file, "%d %d %d\n", &x1, &y, &x2);
      triplets[i][0] = x1;
      triplets[i][1] = y;
      triplets[i][2] = x2;
   }
   roof_line_t *roof_line = construct_line(triplets, size);
   fclose(file);
   return roof_line;
}

roof_line_t *read_answer_file(char *filename)
{
   FILE *file = fopen(filename, "r");
   roof_line_t *roof_line = malloc(sizeof(roof_line_t));

   int x, y;
   node_t *current = NULL;
   node_t *node;
   while (fscanf(file, "(%d,%d)\n", &x, &y) != EOF)
   {
      node = malloc(sizeof(node_t));
      node->x = x;
      node->y = y;
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
   fclose(file);
   current->next = NULL;
   return roof_line;
}

void test_func(char *filename)
{
   char input[strlen("tests/") + strlen(filename) + strlen("-input.txt")];
   strcpy(input, "tests/");
   strcpy(&input[strlen("tests/")], filename);
   strcpy(&input[strlen("tests/") + strlen(filename)], "-input.txt");

   char output[strlen("tests/") + strlen(filename) + strlen("-output.txt")];
   strcpy(output, "tests/");
   strcpy(&output[strlen("tests/")], filename);
   strcpy(&output[strlen("tests/") + strlen(filename)], "-output.txt");

   roof_line_t *test = read_test_file(input);

   roof_line_t *correct_answer = read_answer_file(output);
   printf("\nExpected : ");
   print_roof_line(correct_answer);
   printf("\nResult : ");

   roof_line_t *decompressed_line = decompress_line(test);
   print_roof_line(decompressed_line);

   int res = equals_lines(decompressed_line, correct_answer);

   free_roof_line(test);
   free_roof_line(decompressed_line);
   free_roof_line(correct_answer);

   if (res)
   {
      printf("\nTest %d : success\n\n--------------------------------------\n", test_number);
   }
   else
   {
      printf("\nTest %d : fail\n\n--------------------------------------\n", test_number);
   }
   test_number++;
}

int main()
{
   test_func("tp1-la-ligne-des-toits-271915984");
   test_func("tp1-la-ligne-des-toits-620227487");
   test_func("tp1-la-ligne-des-toits-698049672");
   test_func("tp1-la-ligne-des-toits-1001610599");
   test_func("tp1-la-ligne-des-toits-1085866537");
   test_func("tp1-la-ligne-des-toits-1147394754");
   test_func("tp1-la-ligne-des-toits-1265147860");
   test_func("tp1-la-ligne-des-toits-1611906190");
   test_func("tp1-la-ligne-des-toits-2127497495");
   return 0;
}