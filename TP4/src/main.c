#include "process.h"

int main(void)
{
    // srand(time(NULL));

    process_file_t *process_file = parse_process_file("SMTWP/n100_15_b.txt");

    // for (int i = 0; i < process_file->nb_processes; i++)
    // {
    //     process_t process = process_file->processes[i];
    //     printf("%d %d %d\n", process.time, process.weight, process.limit_time);
    // }

    int nb_processes = process_file->nb_processes;
    process_t *processes = process_file->processes;

    int ordonnancement_sorted[nb_processes];
    for (int i = 0; i < nb_processes; i++)
    {
        ordonnancement_sorted[i] = i;
    }
    int ordonnancement[process_file->nb_processes];

    memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
    constructive_heuristique(ordonnancement, processes, nb_processes);
    int delay = sum_total_delay(processes, nb_processes, ordonnancement);
    printf("Delay with constructive heuristic (sort with delay): %d\n", delay);

    memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
    hill_climbing(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1);
    delay = sum_total_delay(processes, nb_processes, ordonnancement);
    printf("Delay after hill climbing: %d\n", delay);

    memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
    vnd(ordonnancement, processes, nb_processes);
    delay = sum_total_delay(processes, nb_processes, ordonnancement);
    printf("Delay after vnd: %d\n", delay);

    memcpy(ordonnancement, ordonnancement_sorted, nb_processes * sizeof(int));
    ils(ordonnancement, processes, nb_processes, swap_i_and_i_plus_1_three_times);
    delay = sum_total_delay(processes, nb_processes, ordonnancement);
    printf("Delay after ils: %d\n", delay);

    free(processes);
    free(process_file);
    return 0;
}