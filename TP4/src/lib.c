#include "lib.h"

process_file_t *parse_process_file(char *path)
{
   FILE *file = fopen(path, "r");
   int nb_processes = 0;
   if (fscanf(file, "%d", &nb_processes) != 1)
   {
      return NULL;
   }
   process_file_t *process_file = malloc(sizeof(process_file_t));
   process_file->nb_processes = nb_processes;
   process_t *processes = malloc(nb_processes * sizeof(process_t));
   process_file->processes = processes;
   for (int i = 0; i < nb_processes; i++)
   {
      int pi;
      int wi;
      int di;
      if (fscanf(file, "\n%d %d %d", &pi, &wi, &di) != 3)
      {
         free(process_file->processes);
         free(process_file);
         return NULL;
      }
      process_t process = {pi, wi, di};
      processes[i] = process;
   }
   return process_file;
}