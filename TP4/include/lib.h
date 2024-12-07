#ifndef INCLUDE_LIB_H
#define INCLUDE_LIB_H

#include "process.h"

typedef struct
{
   int nb_processes;
   process_t *processes;
} process_file_t;

process_file_t *parse_process_file(char *path);

#endif // INCLUDE_LIB_H