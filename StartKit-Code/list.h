/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

extern int g_fcfsAWTCounter;
extern int g_sjfAWTCounter;
extern int g_rrAWTCounter;
extern int g_pryAWTCounter;
extern int g_pryRRAWTCounter;

struct node {
    Task *task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);
