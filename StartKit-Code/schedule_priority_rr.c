#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

void add(char *name, int priority, int burst);
void schedule();
Task *pickNextTask();
void priorityInsert(struct node **head, Task *newTask);
Task *pickNextNextTask();

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
    int counter = g_pryRRAWTCounter;
    double termination = 0;
    int newTime = 0;
    while (g_processList != NULL)
    {
        Task *currentTask = pickNextTask();
        Task *nextTask = pickNextNextTask();
        newTime = currentTask->burst;
        // int test = currentTask->priority - g_processList->next->task->priority;
        int test2 = currentTask->priority;
        int test3 = nextTask->priority;
        // printf("TEST %d", test);
        // printf("TEST %d\n", test2);
        // printf("TEST3 %d", test3);
        
        if(newTime > QUANTUM){
            run(currentTask, QUANTUM);
            totalTime = totalTime + (QUANTUM * (g_pryRRAWTCounter - 1));
        }else{
            run(currentTask, currentTask->burst);
            totalTime = totalTime + (currentTask->burst * (g_pryRRAWTCounter - 1));
        }
        currentTask->burst = currentTask->burst - QUANTUM;
        delete(&g_processList, currentTask);
        while(currentTask->burst > 0){
            add(currentTask->name, currentTask->priority,currentTask->burst);
            g_pryRRAWTCounter++;
            break;
        }
        termination = termination + currentTask->burst;
        totalTurnAround = totalTurnAround + termination;
        g_pryRRAWTCounter -= 1;
        /* code */
    }
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

Task *pickNextNextTask()
{
    struct node *pryList = g_processList;
    Task *priorityTask = pickNextTask();
      while(pryList != NULL)
        {
        if(pryList->task->priority >= priorityTask->priority)
        {
            priorityTask = pickNextTask();
        }
        pryList = pryList->next;
        }
    return priorityTask;
}