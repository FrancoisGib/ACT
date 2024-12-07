#include "process.h"

// double limit_time_value_function(process_t *process)
// {
//     return process->limit_time;
// }

// double weight_over_time_value_function(process_t *process)
// {
//     return (double)process->weight / (double)process->time;
// }

// double sum_delay_value_function(process_t *process)
// {
//     return (double)(process->limit_time * process->weight);
// }

// double weight_times_1_over_limit(process_t *process)
// {
//     return (double)((double)process->weight * (1 / (double)process->limit_time));
// }

int sum_total_delay(process_t *processes, int nb_processes, int *ordonnancement)
{
    int delay = 0;
    int current_time = 0;
    for (int i = 0; i < nb_processes; i++)
    {
        int task = ordonnancement[i];
        process_t process = processes[task];
        current_time += process.time;
        if (current_time - process.limit_time > 0)
            delay += (current_time - process.limit_time) * process.weight;
    }
    return delay;
}

void generate_random_solution(int *ordonnancement, int nb_processes)
{
    char already_ordonated[nb_processes];
    memset(already_ordonated, 0, nb_processes);

    int i = 0;
    while (i < nb_processes)
    {
        int random = rand() % nb_processes;
        if (!already_ordonated[random])
        {
            already_ordonated[random] = 1;
            ordonnancement[random] = i;
            i++;
        }
    }
}

process_file_t *parse_file(char *path)
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

void constructive_heuristique(int *ordonnancement, process_t *processes, int nb_processes)
{
    char already_taken[nb_processes];
    memset(already_taken, 0, nb_processes);
    int time = 0;
    for (int i = 0; i < nb_processes; i++)
    {
        int current_loss = INT_MAX;
        int index = -1;
        for (int j = 0; j < nb_processes; j++)
        {
            process_t process = processes[j];
            int take_loss = MAX(0, (process.limit_time - time + process.time) * (1 / process.weight));
            if ((take_loss < current_loss || index == -1) && !already_taken[j])
            {
                index = j;
                current_loss = take_loss;
            }
        }
        printf("loss: %d, time: %d, weight: %d limit: %d\n", current_loss, processes[index].time, processes[index].weight, processes[index].limit_time);
        already_taken[index] = 1;
        ordonnancement[i] = index;
    }
}

void test(process_t *processes, int nb_processes, value_function func)
{
    int ordonnancement_constructive_heuristique[nb_processes];
    int *ordonnancement_constructive_heuristique_ptr = ordonnancement_constructive_heuristique;
    quicksort(processes, 0, nb_processes - 1, func);
    for (int i = 0; i < nb_processes; i++)
    {
        ordonnancement_constructive_heuristique[i] = i;
    }
    int delay = sum_total_delay(processes, nb_processes, ordonnancement_constructive_heuristique_ptr);
    printf("Delay: %d\n", delay);
}

int **generate_neighbors(int *ordonnancement, int nb_processes, swap_function swap_func)
{
    int nb_neighbors = nb_processes - 1;
    int **neighbors = malloc(nb_neighbors * sizeof(int *));
    int sorted_ordonnancement[nb_processes];
    // Sort tasks
    for (int i = 0; i < nb_processes; i++)
    {
        int found = 0;
        int j = 0;
        while (!found && j < nb_processes)
        {
            if (ordonnancement[j] == i)
            {
                sorted_ordonnancement[i] = j;
                found = 1;
            }
            j++;
        }
    }

    for (int i = 0; i < nb_processes - 1; i++)
    {
        int *neighbor = malloc(nb_processes * sizeof(int));
        neighbors[i] = neighbor;
        // Copy all tasks
        memcpy(neighbor, ordonnancement, nb_processes * sizeof(int));
        // Swap
        swap_func(neighbor, sorted_ordonnancement, nb_processes, i);
    }
    return neighbors;
}

int *hill_climbing(int *current_ordonnancement, process_t *processes, int nb_processes)
{
    int **neighbors = generate_neighbors(current_ordonnancement, nb_processes, swap_i_and_i_plus_1);
    int nb_ordonnancements = nb_processes - 1;
    int current_ordonnancement_delay = sum_total_delay(processes, nb_processes, current_ordonnancement);
    int best_delay = current_ordonnancement_delay;
    int best_ordonnancement_index = -1;
    for (int i = 0; i < nb_ordonnancements; i++)
    {
        int delay = sum_total_delay(processes, nb_processes, neighbors[i]);
        if (delay < best_delay)
        {
            best_delay = delay;
            best_ordonnancement_index = i;
        }
    }

    if (best_ordonnancement_index == -1)
    {
        return current_ordonnancement;
    }

    int *best_ordonnancement = malloc(nb_processes * sizeof(int));
    memcpy(best_ordonnancement, neighbors[best_ordonnancement_index], nb_processes * sizeof(int));

    for (int i = 0; i < nb_ordonnancements; i++)
    {
        free(neighbors[i]);
    }
    free(neighbors);

    if (best_delay < current_ordonnancement_delay)
    {
        return hill_climbing(best_ordonnancement, processes, nb_processes);
    }
    return best_ordonnancement;
}

int *get_best_neighbor_and_free(int **neighbors, process_t *processes, int nb_processes)
{
    int nb_neighbors = nb_processes - 1;
    int best_delay = INT_MAX;
    int *best_neighbor = malloc(nb_processes * sizeof(int));
    for (int i = 0; i < nb_neighbors; i++)
    {
        int *neighbor = neighbors[i];
        int neighbor_delay = sum_total_delay(processes, nb_processes, neighbor);
        if (neighbor_delay < best_delay)
        {
            memcpy(best_neighbor, neighbor, nb_processes * sizeof(int));
            best_delay = neighbor_delay;
        }
        free(neighbor);
    }
    free(neighbors);
    return best_neighbor;
}

int *vnd(int *initial_ordonnancement, process_t *processes, int nb_processes, int k)
{
    int nb_ordonnancements = nb_processes - 1;
    int best_ordonnancement_index = -1;
    int i = 0;
    int *current_ordonnancement = malloc(nb_processes * sizeof(int));
    memcpy(current_ordonnancement, initial_ordonnancement, nb_processes * sizeof(int));
    int current_delay = sum_total_delay(processes, nb_processes, initial_ordonnancement);

    while (i < k)
    {
        int **neighbors = generate_neighbors(current_ordonnancement, nb_processes, swap_i_and_middle);
        int *best_neighbor = get_best_neighbor_and_free(neighbors, processes, nb_processes);
        int neighbor_delay = sum_total_delay(processes, nb_processes, best_neighbor);
        if (neighbor_delay < current_delay)
        {
            current_delay = neighbor_delay;
            memcpy(current_ordonnancement, best_neighbor, nb_processes * sizeof(int));
            i = 0;
        }
        else
        {
            i++;
        }
        free(best_neighbor);
    }
    return current_ordonnancement;
}

int main(void)
{
    srand(time(NULL));
    process_t processes[] = {{5, 3, 10}, {6, 2, 10}, {12, 5, 15}, {8, 3, 20}};
    process_t *processes_ptr = processes;
    int nb_processes = sizeof(processes) / sizeof(process_t);

    int ordonnancement[] = {2, 0, 1, 3};
    // int *ordonnancement_ptr = ordonnancement;

    // int delay = sum_total_delay(processes_ptr, nb_processes, ordonnancement_ptr);
    // printf("Delay: %d\n", delay);

    // int random_ordonnancement[nb_processes];
    // int *random_ordonnancement_ptr = random_ordonnancement;
    // generate_random_solution(random_ordonnancement_ptr, nb_processes);

    // printf("Random ordonnancement: ");
    // for (int i = 0; i < nb_processes; i++)
    // {
    //     printf("%d ", random_ordonnancement[i]);
    // }
    // printf("\n");

    process_file_t *process_file = parse_file("SMTWP/n100_15_b.txt");

    for (int i = 0; i < process_file->nb_processes; i++)
    {
        process_t process = process_file->processes[i];
        printf("%d %d %d\n", process.time, process.weight, process.limit_time);
    }

    // int random_ordonnancement2[process_file->nb_processes];
    // int *random_ordonnancement_ptr2 = random_ordonnancement2;
    // generate_random_solution(random_ordonnancement_ptr2, process_file->nb_processes);

    // delay = sum_total_delay(process_file->processes, process_file->nb_processes, random_ordonnancement_ptr2);
    // printf("Delay: %d\n", delay);

    // quicksort(process_file->processes, 0, process_file->nb_processes - 1, weight_over_time_value_function);
    // for (int i = 0; i < process_file->nb_processes; i++)
    // {
    //     process_t process = process_file->processes[i];
    //     printf("%d %d %d\n", process.time, process.weight, process.limit_time);
    // }

    int ordonnancement_sorted[process_file->nb_processes];
    for (int i = 0; i < process_file->nb_processes; i++)
    {
        ordonnancement_sorted[i] = i;
    }
    int *ordonnancement_sorted_ptr = ordonnancement_sorted;
    // delay = sum_total_delay(process_file->processes, process_file->nb_processes, ordonnancement_sorted_ptr);
    // printf("Delay: %d\n", delay);

    // test(process_file->processes, process_file->nb_processes, weight_times_1_over_limit);
    // free(process_file->processes);
    // free(process_file);

    // test(processes_ptr, nb_processes, weight_times_1_over_limit);
    // printf("\n");

    int *ordonnancement_ptr = ordonnancement_sorted_ptr;
    nb_processes = process_file->nb_processes;
    processes_ptr = process_file->processes;

    int delay = sum_total_delay(processes_ptr, nb_processes, ordonnancement_ptr);
    printf("delay: %d\n", delay);

    // int **neighbors = generate_neighbors(ordonnancement_ptr, nb_processes, swap_i_and_i_plus_1);

    // for (int i = 0; i < nb_processes - 1; i++)
    // {
    //     int delay = sum_total_delay(processes_ptr, nb_processes, neighbors[i]);
    //     printf("delay: %d\n", delay);
    // }

    // test(processes_ptr, nb_processes, weight_times_1_over_limit);
    constructive_heuristique(ordonnancement_ptr, processes_ptr, nb_processes);
    int delay_before = sum_total_delay(processes_ptr, nb_processes, ordonnancement_ptr);
    printf("\nDelay before hill climbing: %d\n", delay_before);
    int *best_ordonnancement = hill_climbing(ordonnancement_ptr, processes_ptr, nb_processes);

    int delay_after = sum_total_delay(processes_ptr, nb_processes, best_ordonnancement);
    printf("Delay after hill climbing: %d\n", delay_after);

    best_ordonnancement = vnd(ordonnancement_ptr, processes_ptr, nb_processes, 1000);
    // best_ordonnancement = hill_climbing(best_ordonnancement, processes_ptr, nb_processes);

    delay_after = sum_total_delay(processes_ptr, nb_processes, best_ordonnancement);
    printf("Delay after vnd: %d\n", delay_after);

    process_t tasks[10] = {
        {3, 4, 10}, // Temps = 3, Poids = 4, Limite = 10
        {5, 2, 8},  // Temps = 5, Poids = 2, Limite = 8
        {2, 3, 6},  // Temps = 2, Poids = 3, Limite = 6
        {4, 6, 15}, // Temps = 4, Poids = 6, Limite = 15
        {3, 5, 7},  // Temps = 3, Poids = 5, Limite = 7
        {6, 2, 20}, // Temps = 6, Poids = 2, Limite = 20
        {1, 4, 5},  // Temps = 1, Poids = 4, Limite = 5
        {7, 3, 12}, // Temps = 7, Poids = 3, Limite = 12
        {3, 7, 10}, // Temps = 3, Poids = 7, Limite = 10
        {2, 1, 4}   // Temps = 2, Poids = 1, Limite = 4
    };

    int n = 10;

    return 0;
}