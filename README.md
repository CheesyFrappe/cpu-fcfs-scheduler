# FCFS CPU-Scheduler

This is a five-state OS simulation that has been scheduled by the [FCFS](https://en.wikipedia.org/wiki/Scheduling_(computing)#First_come,_first_served) (first come, first serve) algorithm.

This operating system should contain these states: `NEW`, `READY`, `RUN`, `BLOCKED`, and `EXIT`. When the processes are in `READY` and `BLOCKED`, they will be saved in a queue.


## `project.c`
It contains the `main()` and the functions that allow the program to run and give the desired output.

It also contains a structure for each Process. The structure contains as follows:
  - `state`, ranging from 0 to 5 (int)
  - `id`, being unique to that process, the first one being 0 (int)
  - `timer`, that each state can take (int)
  - `index`, that is on its Array of states, mostly functions like the y in the int processes[x][y] that is given to us as an input (int)
  - `flag`, that states whether the process has started, ended, or is still running. (int)


## `main()`
The main contains the functions of the program and contains the input array. Its capacity is obtained via the function `CountProcess()`, which is then used to build the header (via the `PrintHeader()` function) and it’s also used in the simulation (`FCFS()` function). It prints an ”END!” once it’s finished. This program also contains a Queue in order to organize the process order. Processes were chosen to be represented with a structure.

## `FCFS()`
This is the function of our algorithm, ”First Come, First Served”. The first process to run will always be the first one that arrived in that Queue, if a process needs to run, its Id will be saved on a Queue. The function returns nothing, but instead, it prints the results of our program and executes everything accordingly. It initiates and saves each process in an Array (`processArray`) and saves their IDs in a Queue (`processQueue`), and once this Queue is Empty, the program stops and prints an ”END!”.

## Queue structure:
A Queue was used to organize the order of the processes in this program. It saves the values of the id of each process and uses that value to decide what process should be the one Running next. The file `queue.c` contains commands that allow us to create a Queue, Enqueuing, and Dequeue id’s, if it is full or empty, check the successor (the Id after a certain Id) and the Id that is next to Run. It also has a function called `FrontAndDequeue()`, which allows us to check both the Id on the Front and Dequeue it. Whenever a process is next to run, it should be Dequeued and, whenever a value is Enqueued, it must wait on the READY state until it is ready to change to the RUNNING state.

## Output
[Report file](https://github.com/CheesyFrappe/cpu-fcfs-scheduler/blob/master/document/17048_42650-3.pdf) contains two outputs of two different files. The first output is given by the course instructors which is the first test in [Testes](https://github.com/CheesyFrappe/cpu-fcfs-scheduler/blob/master/document/Testes.pdf). The pdf file contains other tests as well as the second one.

## Usage
```sh
   ...
   ```

