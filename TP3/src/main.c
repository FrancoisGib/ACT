#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
    int nb_bags;
    int max_bag_weight;
} bin_pack_t;

void print_certificate(int cert[], int nb_objects)
{
    for (int i = 0; i < nb_objects; i++)
    {
        printf("%d ", cert[i]);
    }
    printf("\n");
}

int verify_certificate(int *certificate, int cert_size, int *objects, int nb_objects, bin_pack_t bags)
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

int **enumerate_certificates(int nb_objects, int nb_bags)
{
    int cert[nb_objects];
    memset(cert, 0, sizeof(int) * nb_objects);

    int nb_certificates = pow(nb_bags, nb_objects);
    int **certificates = malloc(sizeof(int *) * nb_certificates);

    int cpt = 0;
    int i = nb_objects - 1;
    while (cpt < nb_certificates) // nb_bags^nb_objects tours
    {
        int *certificate = malloc(sizeof(int) * nb_objects);
        memcpy(certificate, cert, sizeof(int) * nb_objects);
        certificates[cpt] = certificate;
        cpt++;
        i = nb_objects - 1;
        while (i >= 0 && cert[i] == nb_bags - 1)
        {
            cert[i] = 0; // on remet à 0 si on atteint le nombre de sacs - 1, si on l'a fait pour tous les objets, alors on a fini.
            i--;
        }
        cert[i]++;
    }
    return certificates;
}

void free_certificates_list(int **certificates, int n)
{
    for (int i = 0; i < n; i++)
        free(certificates[i]);
    free(certificates);
}

int partition(int *elements, int n)
{
    int **certificates = enumerate_certificates(n, 2);
    int nb_certificates = pow(2, n);

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += elements[i];
    }

    bin_pack_t binpack = {.nb_bags = 2, .max_bag_weight = sum / 2 + sum % 2};
    int i = 0;
    int res = 0;
    while (!res && i < nb_certificates)
    {
        if (verify_certificate(certificates[i], n, elements, n, binpack))
        {
            print_certificate(certificates[i], n);
            res = 1;
        }
        i++;
    }

    free_certificates_list(certificates, nb_certificates);
    return res;
}

int sum_red(int *elements, int n, int c)
{
    int sum_elements = 0;
    for (int i = 0; i < n; i++)
    {
        sum_elements += elements[i];
    }
    if (sum_elements >= c * 2)
    {
        return partition(elements, n);
    }
    int new_element_value = 2 * c - sum_elements;
    int new_elements_array[n + 1];
    memcpy(new_elements_array, elements, n * sizeof(int));
    new_elements_array[n] = new_element_value;
    return partition(new_elements_array, n + 1);
}

typedef struct
{
    int nb_bags;
    int *bag_weights;
} bin_pack_diff_t;

int main(void)
{
    int objects[] = {3, 2, 4, 3, 3};
    int nb_objects = sizeof(objects) / sizeof(int);
    int nb_bags = 4;
    int max_bag_weight = 5;
    int certificate[] = {0, 0, 1, 2, 3};
    int cert_size = sizeof(objects) / sizeof(int);

    bin_pack_t bags = {nb_bags, max_bag_weight};

    printf("%d\n\n", verify_certificate(certificate, cert_size, objects, nb_objects, bags));

    int *random_certificate = generate_random_certificate(nb_objects, bags.nb_bags);
    print_certificate(random_certificate, nb_objects);
    free(random_certificate);

    printf("\n");

    int power = pow(3, 3);
    int **certificates = enumerate_certificates(3, 3);
    for (int i = 0; i < power; i++)
    {
        print_certificate(certificates[i], 3);
    }
    free_certificates_list(certificates, power);

    printf("\n");

    int elements[] = {1, 2, 3, 4, 1, 2, 1};
    int nb_elements = sizeof(elements) / sizeof(int);
    int res = partition(elements, nb_elements);
    printf("partition: %d\n", res);

    res = sum_red(elements, nb_elements, 10);
    printf("sum: %d\n", res);
}