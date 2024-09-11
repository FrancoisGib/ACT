#include "roof_line.h"

extern int loop_count;

int main()
{
    int data[][3] = {
        {10, 4, 20},
        {20, 4, 22},
        {15, 5, 23},
        {17, 4, 24},
        {24, 10, 100},
        {40, 8, 90},
        {8, 2, 120},
        {130, 7, 140}};

    int n = sizeof(data) / sizeof(data[0]);

    roof_line_t *merged = construct_line(data, n);
    printf("Compressed line : ");
    print_roof_line(merged);

    roof_line_t *decompressed_line = decompress_line(merged);
    free_roof_line(merged);

    printf("Uncompressed line : ");
    print_roof_line(decompressed_line);
    free_roof_line(decompressed_line);

    generate_svg_file("file.html", data, n);

    printf("rec %d\n", loop_count);
    return 0;
}