#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    int nb_bags;
    int max_bag_weight;
} bin_packs_t;

void print_certificate(int cert[], int nb_objects)
{
    for (int i = 0; i < nb_objects; i++)
    {
        printf("%d ", cert[i]);
    }
    printf("\n");
}

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

void enumerate_certificates(int nb_objects, int nb_bags)
{
    int cert[nb_objects];
    memset(cert, 0, sizeof(int) * nb_objects);

    int i = nb_objects - 1;
    while (i >= 0) // nb_bags^nb_objects tours
    {
        print_certificate(cert, nb_objects);
        i = nb_objects - 1;
        while (cert[i] == nb_bags - 1)
        {
            cert[i] = 0; // on remet à 0 si on atteint le nombre de sacs - 1, si on l'a fait pour tous les objets, alors on a fini.
            i--;
        }
        cert[i]++;
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
    print_certificate(random_certificate, nb_objects);
    free(random_certificate);

    printf("\n");

    enumerate_certificates(2, 3);
}