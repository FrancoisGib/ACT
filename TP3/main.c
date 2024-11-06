#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_array(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

typedef struct
{
    int nb_bags;
    int max_bag_weight;
} bin_packs_t;

int verify_certificate(int *certificate, int cert_size, int *objects, int nb_objects, bin_packs_t bags)
{
    if (cert_size != nb_objects)
    {
        return 0;
    }

    int sum_bags_weight[bags.nb_bags];
    memset(sum_bags_weight, 0, sizeof(int) * bags.nb_bags);

    for (int i = 0; i < nb_objects; i++)
    {
        int bag_index = certificate[i];
        sum_bags_weight[bag_index] += objects[i];
        if (sum_bags_weight[bag_index] > bags.max_bag_weight)
        {
            return 0;
        }
    }

    return 1;
}

int *generate_random_certificate(int nb_objects, int nb_bags)
{
    srand(time(NULL));
    int *certificate = malloc(sizeof(int) * nb_objects);
    for (int i = 0; i < nb_objects; i++)
    {
        certificate[i] = rand() % nb_bags;
    }
    return certificate;
}

void enumerate_cell(int *certificate, int n, int nb_bags, int nb_objects)
{
    for (int i = 0; i < nb_bags; i++)
    {
        certificate[n - 1]++;
        print_array(certificate, nb_objects);
    }
    // printf("arr ");
    // certificate[n] = 0;
}

void enumerate_column(int *certificate, int n, int nb_bags, int nb_objects)
{
    certificate[n] = 0;
    enumerate_cell(certificate, n + 1, nb_bags, nb_objects);
    print_array(certificate, nb_objects);
    // for (int i = 0; i < nb_bags; i++)
    // {
    //     certificate[n]++;
    //     enumerate_cell(certificate, i + n + 1, nb_bags, nb_objects);
    //     print_array(certificate, nb_objects);
    // }
    // for (int i = 0; i < nb_objects - n; i++)
    // {
    //     enumerate_cell(certificate, i + n, nb_bags, nb_objects);
    // }
}

void enumerate_certificates(int nb_objects, int nb_bags)
{
    int certificate[nb_objects];
    memset(certificate, 0, sizeof(int) * nb_objects);

    print_array(certificate, nb_objects);
    for (int j = nb_objects - 1; j >= 0; j--)
    {
        // memset(&certificate[j + 1], 0, sizeof(int) * (nb_objects - 1 - j));
        enumerate_column(certificate, j, nb_bags, nb_objects);
    }
}

int main()
{
    int objects[] = {3, 2, 4, 3, 3};
    int nb_objects = sizeof(objects) / sizeof(int);
    int nb_bags = 4;
    int max_bag_weight = 5;
    int certificate[] = {0, 0, 1, 2, 3};
    int cert_size = sizeof(objects) / sizeof(int);

    bin_packs_t bags = {nb_bags, max_bag_weight};

    printf("%d\n\n", verify_certificate(certificate, cert_size, objects, nb_objects, bags));

    int *random_certificate = generate_random_certificate(nb_objects, bags.nb_bags);
    print_array(random_certificate, nb_objects);
    free(random_certificate);

    printf("\n");

    enumerate_certificates(3, 2);
}