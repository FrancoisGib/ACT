#include "process.h"

double limit_time_value_function(process_t *process)
{
    return process->limit_time;
}

double weight_over_time_value_function(process_t *process)
{
    return (double)process->weight / (double)process->time;
}

double sum_delay_value_function(process_t *process)
{
    return (double)(process->limit_time * process->weight);
}

double weight_times_1_over_limit(process_t *process)
{
    return (double)((double)process->weight * (1 / (double)process->limit_time));
}

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
    int loss = 0;
    int time = 0;
    int index = 0;
    for (int i = 0; i < nb_processes; i++)
    {
        int local_loss = INT_MAX;
        for (int j = 0; j < nb_processes; j++)
        {
            if (already_taken[j])
            {
                continue;
            }
            int end_time = time + processes[j].time;
            int delay_loss = MAX(0, processes[j].weight * (end_time - processes[j].limit_time));
            if (delay_loss < local_loss)
            {
                index = j;
                local_loss = delay_loss;
            }
        }
        ordonnancement[i] = index;
        already_taken[index] = 1;
        time += processes[index].time;
        loss += local_loss;
        index = 0;
    }
}

void constructive_heuristique2(int *ordonnancement, process_t *processes, int nb_processes, value_function func)
{
    char already_taken[nb_processes];
    memset(already_taken, 0, nb_processes);
    int time = 0;
    for (int i = 0; i < nb_processes; i++)
    {
        int current_loss = 0;
        int index = 0;
        for (int j = 0; j < nb_processes; j++)
        {
            if (already_taken[j])
                continue;
            double j_value = func(&processes[j]);
            // int j_loss = MAX(0, (time + processes[j].time - processes[j].limit_time) * processes[j].weight);
            int j_loss = 0;
            if ((j_value + j_loss) < (func(&processes[index]) + current_loss))
            {
                current_loss = j_loss;
                index = j;
            }
        }
        time += processes[index].time;
        ordonnancement[i] = index;
        already_taken[index] = 1;
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

void test2(process_t *processes, int nb_processes, value_function func)
{
    int ordonnancement_constructive_heuristique[nb_processes];
    int *ordonnancement_constructive_heuristique_ptr = ordonnancement_constructive_heuristique;
    constructive_heuristique2(ordonnancement_constructive_heuristique_ptr, processes, nb_processes, func);
    for (int i = 0; i < nb_processes; i++)
    {
        printf("%d ", ordonnancement_constructive_heuristique[i]);
    }
    int delay = sum_total_delay(processes, nb_processes, ordonnancement_constructive_heuristique_ptr);
    printf("Delay: %d\n", delay);
}

int **generate_neighbors(int *ordonnancement, int nb_processes)
{
    int nb_neighbors = nb_processes - 1;
    int **neighbors = malloc(nb_neighbors * sizeof(int *));
    int sorted_ordonnancement[nb_processes];
    // Sort tasks
    for (int i = 0; i < nb_processes; i++)
    {
        int found = 0;
        int j = 0;
        while (!found && j < nb_processes) {
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
        int* neighbor = malloc(nb_processes * sizeof(int));
        neighbors[i] = neighbor;
        // Copy all tasks
        memcpy(neighbor, ordonnancement, nb_processes * sizeof(int));
        // Switch the two tasks
        neighbor[sorted_ordonnancement[i + 1]] = i;
        neighbor[sorted_ordonnancement[i]] = i + 1;
    }
    return neighbors;
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

    quicksort(process_file->processes, 0, process_file->nb_processes - 1, weight_over_time_value_function);
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

    for (int j = 0; j < nb_processes; j++)
    {
        // printf("%d ", ordonnancement[j]);
    }
    int delay = sum_total_delay(processes_ptr, nb_processes, ordonnancement_ptr);
    printf("delay: %d\n", delay);

    int **neighbors = generate_neighbors(ordonnancement_ptr, nb_processes);

    for (int i = 0; i < nb_processes - 1; i++) {
        int delay = sum_total_delay(processes_ptr, nb_processes, neighbors[i]);
        for (int j = 0; j < nb_processes; j++)
        {
            // printf("%d ", neighbors[i][j]);
        }
        printf("delay: %d\n", delay);
    }

    return 0;
}