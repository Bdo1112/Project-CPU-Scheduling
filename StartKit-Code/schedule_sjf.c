#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "task.h"
#include "list.h"
#include "cpu.h"

Task *pickNextTask();
void add(char *name, int priority, int burst);
void schedule();

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
    double sjfTotalTime = 0;
    double sjfTotalTurnAround = 0;
    int sjfCounter = 0;
    double sjfTermination = 0;
    while (g_processList != NULL)
    {
        Task *currentTask = pickNextTask();
        run(currentTask, currentTask->burst);
        
        sjfCounter += 1;
        sjfTotalTime = sjfTotalTime + currentTask->burst * (g_sjfAWTCounter - 1);
        g_sjfAWTCounter = g_sjfAWTCounter - 1;
        sjfTermination = sjfTermination + currentTask->burst;
        sjfTotalTurnAround = sjfTotalTurnAround + sjfTermination;
        // printf("sjfTotalTimeTest %f\n", sjfTotalTime);
        // printf("sjfTotalTimeTest %d\n", g_sjfAWTCounter);
        // printf("sjfCounterTest %d\n", sjfCounter);
        
        delete(&g_processList, currentTask);
        // printf("test");
        /* code */
    } 

    printf("\n");
    printf("Average waiting time = %.2f\n", sjfTotalTime / sjfCounter);
    printf("Average turnaround time = %.2f\n", sjfTotalTurnAround / sjfCounter);
    printf("Average response time = %.2f\n", sjfTotalTime / sjfCounter);

}

Task *pickNextTask()
{
    struct node *sjfList = g_processList;
    //copy g_processList into sjfList

    Task *sjf = g_processList->task;
    //point sjf to the first task of g_processList
    //by using g_processList->task

    while(sjfList != NULL)
    {
        if(sjf->burst >= sjfList->task->burst)
        {
            sjf = sjfList->task;
        }
        sjfList = sjfList->next;
    }

    // while(sjfList != NULL)
    // {
    //     printf(sjfList->task);
    //     sjfList->next;
    // }

    return sjf;
};






