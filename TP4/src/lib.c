#include "lib.h"

process_file_t *parse_process_file(char *path)
{
   FILE *file = fopen(path, "r");
   int nb_processes = 0;
   if (fscanf(file, "%d", &nb_processes) != 1)
   {
      fclose(file);
      return NULL;
   }
   process_file_t *process_file = malloc(sizeof(process_file_t));
   process_file->nb_processes = nb_processes;
   process_t *processes = malloc(nb_processes * sizeof(process_t));
   process_file->processes = processes;
   for (int i = 0; i < nb_processes; i++)
   {
      int pi, wi, di;
      if (fscanf(file, "\n%d %d %d", &pi, &wi, &di) != 3)
      {
         free(process_file->processes);
         free(process_file);
         fclose(file);
         return NULL;
      }
      process_t process = {pi, wi, di};
      processes[i] = process;
   }
   fclose(file);
   return process_file;
}

void parse_solutions_file(char *path, int *solutions_array, int nb_files)
{
   FILE *file = fopen(path, "r");
   for (int i = 0; i < nb_files; i++)
   {
      int dummy1, dummy2;
      if (fscanf(file, "%d_%d : %d\n", &dummy1, &dummy2, &solutions_array[i]) != 3)
      {
         fclose(file);
         return;
      }
   }
   fclose(file);
}