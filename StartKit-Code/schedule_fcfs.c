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
    int counter = 0;
    int termination = 0;
    while (g_processList != NULL)
    {
        Task *currentTask;
        currentTask = pickNextTask();
        run(currentTask, currentTask->burst);
        totalTime = totalTime + currentTask->burst * (g_fcfsAWTCounter-1);
        g_fcfsAWTCounter = g_fcfsAWTCounter - 1;
        // printf("\nburst time test %d\n", currentTask->burst);
        // printf("Total Time is **%f\n", totalTime);
        termination = termination + currentTask->burst;
        // printf("current burst time: %d\n", currentTask->burst);
        totalTurnAround = totalTurnAround + termination;
        // printf("termination time : %f\n", totalTurnAround);
        counter += 1;
        delete(&g_processList, currentTask);
        /* code */
    } 

    // printf("\n%f\n", totalTime);
    // printf("%d\n", counter);
    // printf("%d\n", g_fcfsAWTCounter);
    // printf("%f\n", totalTime / counter);
    // printf("total turnaround time is %f\n", totalTurnAround);
    printf("\n");
    printf("Average waiting time = %.2f\n", totalTime / counter);
    printf("Average turnaround time = %.2f\n",totalTurnAround / counter);
    printf("Average response time = %.2f\n",totalTime / counter);
}


Task *pickNextTask()
{
    struct node *fcfsList = g_processList;

    while(fcfsList != NULL)
    {
        if(fcfsList->next == NULL)
        {
            break;
        }
        fcfsList = fcfsList->next;
    }
    return fcfsList->task;
}


