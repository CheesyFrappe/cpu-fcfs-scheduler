#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fatal.h"
#include "project.h"
#include "queue.c"

char states[5][10] =
    {"   NEW   ", "  READY  ", "   RUN   ", "  BLOCK  ", "  EXIT   "};

static int flag = 0; // 0 = cpu is not running, 1 = cpu is running

struct Process
{
    int state; // holds int value stands for states
    int id;    // holds a unique id
    int flag;  // flag = -1 (NEW), flag = 1, flag = 0 (EXIT)
    int timer; // it shows how many instant time will it be printing, it stands for 'RUN' and 'BLOCK'
    int index;     // specifies the index in the table
};

int main(int argc, char *argv[])
{
    int processes[MAX_PROCESS][MAX_STATE] = {
        {1, 3, 1, 2, 2, 4, 0, 0},
        {1, 4, 2, 4, 1, 3, 0, 0},
        {3, 2, 1, 6, 1, 3, 0, 0}};

    int capacity = CountProcess(processes);

    PrintHeader(capacity);

    FCFS(capacity, processes);
    printf("END!\n");

    return 0;
}

// checks if a process is an empty array or not
int Empty(int process[MAX_STATE])
{
    int flag = 1;
    for (int i = 0; i < MAX_STATE; i++)
    {
        if (process[i] != 0)
        {
            flag = 0;
            return flag;
        }
    }

    return flag;
}

// returns 1 if there is/are process(es) waiting in ready queue
int ReadyCheck(int capacity, Process *processArray)
{
    for (int i = 0; i < capacity; i++)
    {
        if (processArray[i]->state == 1)
            return 1;
    }
    return 0;
}

// removes value from queue and sets order of queue to original form
void RemoveFromQueue(Queue q, int id)
{
    int front = Front(q);
    int x = FrontAndDequeue(q);

    if (IsEmpty(q))
    {
        return;
    }

    while (Front(q) != front)
    {

        if (x != id)
        {
            Enqueue(x, q);
        }

        x = FrontAndDequeue(q);
    }
}

// Dequeue and Enqueue process until given id is Front value of given queue
void FixQueue(Queue q, int id)
{
    if (IsEmpty(q))
    {
        return;
    }

    while (Front(q) != id)
    {
        int temp = FrontAndDequeue(q);
        Enqueue(temp, q);
    }
}

// returns 1 if there is a process with state of 'NEW'
int CheckNew(Process *processArray, int capacity)
{
    for (int i = 0; i < capacity; i++)
    {
        if (processArray[i]->state == 0)
            return 1;
    }
    return 0;
}

// returns number of processes are/is in process table
int CountProcess(int processes[MAX_PROCESS][MAX_STATE])
{
    int count = 0;
    for (int i = 0; i < MAX_PROCESS; i++)
    {

        if (Empty(processes[i]))
            continue;
        count++;
    }

    return count;
}

// returns a queue full of given processes
Queue InitializeQueue(int capacity, Process *processArray)
{
    Queue processQueue = CreateQueue(capacity);

    for (int i = 0; i < capacity; i++)
    {
        Enqueue(processArray[i]->id, processQueue);
    }

    return processQueue;
}

// returns an array of structs (Process) within given processes
Process *InitializeProcesses(int capacity, int processes[MAX_PROCESS][MAX_STATE])
{
    Process *processArray = malloc(capacity * sizeof(struct Process));

    for (int i = 0; i < capacity; i++)
    {
        Process P = malloc(sizeof(struct Process));
        P->state = 0;
        P->id = i;
        P->flag = -1;
        P->timer = processes[P->id][1];
        P->index = 1;
        processArray[i] = P;
    }

    return processArray;
}

// prints header output for the number of processes
void PrintHeader(int capacity)
{
    printf("Instants: |");
    for (int i = 1; i <= capacity; i++)
    {

        if (i < 10)
        {
            printf("  proc%d  |", i);
        }
        else
        {
            printf("  proc%d |", i);
        }
    }
    printf("\n");
}

// this function runs the FCFS (First Come First Serverd) algorithm
// prints state of process in each instant time and terminates it when the time comes
void FCFS(int capacity, int processes[MAX_PROCESS][MAX_STATE])
{
    Process *processArray = malloc(capacity * sizeof(struct Process));
    processArray = InitializeProcesses(capacity, processes);
    Queue processQueue = InitializeQueue(capacity, processArray);
    int instant = 0;

    for (;;)
    {
        instant++;

        // print instant time column by considering spacing
        if (instant < 10)
        {

            printf("%d:         ", instant);
        }
        else
        {
            printf("%d:        ", instant);
        }

        //  if there is no process to run, job finish
        if (IsEmpty(processQueue))
        {

            for (int i = 0; i < capacity; i++)
            {
                if (processArray[i]->state == 4 && processArray[i]->flag == 1)
                {

                    printf("%s ", states[processArray[i]->state]);
                }
                else
                {

                    printf("          ");
                }
            }

            // after printing last 'EXIT' state of processes, break outermost for loop
            break;
        }

        // iterate through processes
        for (int x = 0; x < capacity; x++)
        {

            // if process is not started yet, printf nothing and continue
            if (processes[processArray[x]->id][0] > instant)
            {

                printf("          ");
                continue;
            }

            // if process state is 'EXIT'
            if (processArray[x]->state == 4)
            {
                // if not terminated, then terminate it
                if (processArray[x]->flag == 1)
                {
                    flag = 0;
                    printf("%s ", states[processArray[x]->state]);
                    processArray[x]->flag = 0;
                }
                // if terminated, print nothing
                else
                {
                    printf("          ");
                }
            }
            // if process state is not 'EXIT', check for the other states
            else
            {
                // if process is 'NEW', print 'NEW' and pass it to a new state
                if (processes[processArray[x]->id][0] == instant)
                {

                    printf("%s ", states[processArray[x]->state]);

                    // if cpu isn't running and ready queue is empty, process jumps into 'RUN' state
                    // otherwise it jumps into 'READY' state
                    if (!flag && !ReadyCheck(capacity, processArray))
                    {
                        processArray[x]->state = 2; // change process state
                        flag = 1;                   // set cpu to running
                    }
                    else
                    {
                        processArray[x]->state = 1; // change process state
                    }
                }
                // if process is in 'READY' state, print 'READY'
                else if (processArray[x]->state == 1)
                {
                    printf("%s ", states[processArray[x]->state]);

                    // if process is last one in queue
                    // or it's process turn to run, jump into 'RUN' state
                    if (((x == 0 && (Front(processQueue) == capacity - 1) && processArray[Front(processQueue)]->timer == 1) || Front(processQueue) == processArray[x]->id))
                    {
                        processArray[x]->state = 2;
                    }
                }
                // if process should run, print 'RUN' and check the timer condition
                else if (processArray[x]->state == 2 && Front(processQueue) == processArray[x]->id)
                {
                    flag = 1;
                    printf("%s ", states[processArray[x]->state]);

                    processArray[x]->timer--;

                    // if timer goes off, check should it be terminated or not
                    // if not then, switch to 'BLOCKED', and set timer for 'BLOCKED' state
                    if (processArray[x]->timer == 0)
                    {
                        Dequeue(processQueue);
                        processArray[x]->index++;

                        // if there is no value in the table, terminate the process
                        if (processArray[x]->index == 8 || processes[x][processArray[x]->index] == 0)
                        {
                            processArray[x]->state = 4;
                            processArray[x]->flag = 1;
                            continue;
                        }
                        Enqueue(processArray[x]->id, processQueue);
                        processArray[x]->state = 3;
                        processArray[x]->timer = processes[x][processArray[x]->index];
                    }
                }
                // if process is in 'BLOCKED' state, check how many instant will it wait and print 'BLOCKED'
                else if (processArray[x]->state == 3)
                {

                    flag = 0;
                    printf("%s ", states[processArray[x]->state]);
                    processArray[x]->timer--;

                    // if timer goes off, switch to 'READY', and set timer for 'READY' state
                    if (processArray[x]->timer == 0)
                    {
                        processArray[x]->index++;

                        // if there is no value in the table, terminate the process
                        if (processArray[x]->index == 8 || processes[processArray[x]->id][processArray[x]->index] == 0)
                        {
                            if (!IsEmpty(processQueue))
                            {
                                RemoveFromQueue(processQueue, processArray[x]->id); // pop process from queue
                            }
                            processArray[x]->state = 4;
                            processArray[x]->flag = 1;
                            continue;
                        }

                        processArray[x]->timer = processes[x][processArray[x]->index];

                        // if cpu isn't running, jump into 'RUN' state
                        // otherwise, jump into 'READY' state
                        if (flag == 0 && Front(processQueue) == processArray[x]->id)
                        {
                            processArray[x]->state = 2;
                        }
                        else
                        {
                            processArray[x]->state = 1;
                            if (flag == 0 && CheckNew(processArray, capacity) == 1)
                            {
                                FixQueue(processQueue, processArray[x]->id);
                                processArray[x]->state = 2;
                                flag = 1;
                            }
                        }
                    }
                }
                // this else state is unnecessary for the algorithm
                // we added it to see if algorithm misses a process 
                // if it prints 'empty', something is wrong
                else
                {
                    printf(" %d", processArray[x]->state);
                    printf(" empty");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}