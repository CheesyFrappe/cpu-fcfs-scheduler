struct Process;
typedef struct Process *Process;

struct QueueRecord;
typedef struct QueueRecord *Queue;

#define MAX_PROCESS 8
#define MAX_STATE 8

int Empty(int process[MAX_STATE]);
int ReadyCheck(int capacity, Process *processArray);
void RemoveFromQueue(Queue q, int id);
void FixQueue(Queue q, int id);
int CheckNew(Process *processArray, int capacity);
int CountProcess(int processes[MAX_PROCESS][MAX_STATE]);
Queue InitializeQueue(int capacity, Process *processArray);
Process *InitializeProcesses(int capacity, int processes[MAX_PROCESS][MAX_STATE]);
void PrintHeader(int capacity);
void FCFS(int capacity, int processes[MAX_PROCESS][MAX_STATE]);