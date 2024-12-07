#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

#include "process.h"

typedef struct
{
   int nb_processes;
   process_t *processes;
} process_file_t;

process_file_t *parse_process_file(char *path);
void parse_solutions_file(char *path, int *solutions_array, int nb_files);

#endif // INCLUDE_LIB_H