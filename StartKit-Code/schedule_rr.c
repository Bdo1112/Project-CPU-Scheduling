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
int checkBurst(struct node ** checker);

struct node *g_processList = NULL;
struct node *g_rrList = NULL;

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
    insert(&g_processList,process);
    insert(&g_rrList,process);
    // printf("The list contains %s,%d,%d \n",g_processList->task->name,g_processList->task->priority,g_processList->task->burst);
}


void schedule()
{
    // struct node * temp = g_processList;

    double rrRTotalTime = 0;
    // double rrtotalTimeAVG = 0;
    double rrTotalTime = 0;
    double rrTotalTurnAround = 0;
    int rrCounter = g_rrAWTCounter;
    // int rrRespondsTimeCounter = g_rrAWTCounter;
    int rrTermination = 0;
    int newTime = 0;
    int taskTurnAroundTime = 0;
   
       while (g_processList != NULL){
        Task *currentTask = pickNextTask();
        newTime = currentTask->burst;
        if(g_rrAWTCounter == 1)
        {
            run(currentTask, currentTask->burst);
            break;
        }else{
            if(newTime > QUANTUM){
            run(currentTask, QUANTUM);
            rrRTotalTime = rrRTotalTime + (QUANTUM * (g_rrAWTCounter - 1 ));
            rrTotalTime = rrTotalTime + (QUANTUM * (g_rrAWTCounter - 1 ));
            rrTotalTurnAround = rrTotalTurnAround + taskTurnAroundTime;
            // printf("%f\n", rrTotalTurnAround);
            // printf("COUNTERRRR%d\n", g_rrAWTCounter);
            rrTermination = 0;
            // printf("Test total time %f\n", rrRTotalTime);

        }else{
            run(currentTask, currentTask->burst);
            rrRTotalTime = rrRTotalTime + (currentTask->burst * (g_rrAWTCounter - 1));
            rrTotalTime = rrTotalTime + (currentTask->burst * (g_rrAWTCounter - 1 ));
            rrTotalTurnAround = rrTotalTurnAround + taskTurnAroundTime;
            // printf("Test total time %f\n", rrRTotalTime);
        }
        currentTask->burst = currentTask->burst - QUANTUM;
        if(currentTask->burst == 0){
            rrTotalTurnAround = rrTotalTurnAround + rrRTotalTime;
        }
        
        delete(&g_processList, currentTask);
        taskTurnAroundTime = rrRTotalTime;
        g_rrAWTCounter -=1;
        /* code */
        if(currentTask->burst > 0){
            add(currentTask->name,currentTask->priority,currentTask->burst);
            taskTurnAroundTime = 0;
            g_rrAWTCounter +=1;
        }
        }
        
        } /* code */
        printf("\n");
        printf("Average waiting time = %.2f\n", rrRTotalTime / rrCounter);
        printf("Average turnaround time = %.2f\n", rrTotalTurnAround / rrCounter);
        printf("Average response time = %.2f\n", rrRTotalTime / rrCounter);
}


Task *pickNextTask()
{
    struct node *fcfsList = g_processList;
    // Task *rrTask = g_rrList->task;
    while(fcfsList->next != NULL)
    {
        if(fcfsList->next == NULL)
        {
            break;
        }
        fcfsList = fcfsList->next;
    }
    return fcfsList->task;
}






