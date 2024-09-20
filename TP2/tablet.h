#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int i;
    int j;
} point_t;

typedef struct
{
    int m;
    int n;
    point_t *point;
} tablet_t;