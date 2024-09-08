#include "roof_line.h"

int main()
{
    int data[][3] = {
        {3, 13, 9},
        {1, 11, 5},
        {19, 18, 22},
        {3, 6, 7},
        {16, 3, 25},
        {12, 7, 16}};

    /*int data[][3] = {
        {98, 41, 127},
        {154, 16, 176},
        {195, 89, 231},
        {201, 22, 215},
        {167, 34, 191}};*/

    /*int data[][3] = {
        {10, 4, 20},
        {20, 4, 22},
        {15, 5, 23},
        {17, 4, 24},
        {24, 10, 100},
        {40, 8, 90},
        {8, 2, 120},
        {130, 7, 140}};*/

    int n = sizeof(data) / sizeof(data[0]);
    roof_line_t *merged = construct_line(data, n);
    printf("Compressed line : ");
    print_roof_line(merged);
    roof_line_t *decompressed_line = decompress_line(merged);
    free_roof_line(merged);
    printf("Uncompressed line : ");
    print_roof_line(decompressed_line);
    free(decompressed_line);
    generate_svg_file("file.html", data, sizeof(data) / sizeof(data[0]));
    return 0;
}