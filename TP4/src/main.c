#include "process.h"

int main(void)
{
    process_file_t *process_file = parse_process_file("SMTWP/n100_15_b.txt");

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

    int *ordonnancement_ptr = ordonnancement_sorted;
    int nb_processes = process_file->nb_processes;
    process_t *processes_ptr = process_file->processes;

    constructive_heuristique(ordonnancement_ptr, processes_ptr, nb_processes);
    int delay = sum_total_delay(processes_ptr, nb_processes, ordonnancement_ptr);
    printf("Delay with constructive heuristic (sort with delay): %d\n", delay);

    int *best_ordonnancement = hill_climbing(ordonnancement_ptr, processes_ptr, nb_processes);
    delay = sum_total_delay(processes_ptr, nb_processes, best_ordonnancement);
    printf("Delay after hill climbing: %d\n", delay);

    best_ordonnancement = vnd(ordonnancement_ptr, processes_ptr, nb_processes, 100000);
    delay = sum_total_delay(processes_ptr, nb_processes, best_ordonnancement);
    printf("Delay after vnd: %d\n", delay);

    return 0;
}