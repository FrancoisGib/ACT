#include "roof_line.h"

extern int operations_count;

void create_worst_case_roof_line(int n, FILE *output)
{
    int triplets[n][3];
    for (int i = 0; i < n; i++)
    {
        triplets[i][0] = i + 1;
        triplets[i][1] = i + 2;
        triplets[i][2] = i + 1;
    }

    roof_line_t *roof_line = construct_line(triplets, n);
    char buf[32];
    sprintf(buf, "%d %d\n", n, operations_count);
    fwrite(buf, strlen(buf), 1, output);
    free_roof_line(roof_line);
    printf("Insertions count for n = %d, %d\n", n, operations_count);
}

int main()
{
    /*
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
    */
    FILE *file = fopen("worst_case.dat", "w");
    for (int i = 10000; i <= 500000; i += 10000)
    {
        operations_count = 0;
        create_worst_case_roof_line(i, file);
    }
    fclose(file);
    return 0;
}
