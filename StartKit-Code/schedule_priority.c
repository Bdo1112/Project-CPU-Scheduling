#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

void add(char *name, int priority, int burst);
void schedule();
Task *pickNextTask();
void priorityInsert(struct node **head, Task *newTask);

struct node *g_processList = NULL;

void add(char *name, int priority, int burst)
{
    // printf("test %s\n", name);
    // printf("The list is %s\n",g_processList);
    Task *process;
    process = malloc(sizeof(Task));
    // printf("%s\n",process->name);
    // printf("%s\n",process->tid);
    // printf("%s\n",process->priority);
    // printf("%s\n",process->burst);
    process->name = malloc(sizeof(char) * (strlen(name)+1));
    strcpy(process->name, name);
    // process->priority = malloc(sizeof(int));
    process->priority = priority;
    process->burst = burst;
    // printf("%s\n",process->name);
    // printf("%d\n",process->tid);
    // printf("%d\n",process->priority);
    // printf("%d\n",process->burst);
    insert(&g_processList, process);
    // printf("The list contains %s,%d,%d \n",g_processList->task->name,g_processList->task->burst,g_processList->task->priority);
}

void schedule()
{
    double totalTime = 0;
    double totalTurnAround = 0;
    int counter = g_pryAWTCounter;
    double termination = 0;
    while (g_processList != NULL)
    {
        Task *currentTask = pickNextTask();
        run(currentTask, currentTask->burst);
        totalTime = totalTime + (currentTask->burst * (g_pryAWTCounter -1 ));
        termination = termination + currentTask->burst;
        totalTurnAround = totalTurnAround + termination;
        g_pryAWTCounter -= 1;
        delete(&g_processList, currentTask);
        /* code */
    } 
    // printf("awtcounter %d\n", g_pryAWTCounter);
    // printf("totalTime %f\n", totalTime);

    printf("\n");
    printf("Average waiting time = %.2f\n", totalTime / counter);
    printf("Average trunaround time = %.2f\n", totalTurnAround / counter);
    printf("Average response time = %.2f\n", totalTime / counter);

}

Task *pickNextTask()
{
    struct node *pryList = g_processList;
    Task *priorityTask = g_processList->task;

    while(pryList != NULL)
    {
        if(pryList->task->priority >= priorityTask->priority)
        {
            priorityTask = pryList->task;
        }
        pryList = pryList->next;
    }
    return priorityTask;
}



