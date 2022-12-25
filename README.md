# Process Scheduling Algorithms Simulation

### First come First Serve

- A normal queue data structure is used in the implementation, where all the incoming processes are sorted in increasing order.
- Then, each process is dequeued and scheduled for the burst_time1 only.
- Assuming infinite I/O devices the io_time is handled and then burst_time2 is scheduled again in the same increasing arrival time fashion.

### Shortest Job First:

- The implementation details of SJF and FCFS are almost identical in many ways such as - they are not preemptive, the scheduling is done on the basis of a time parameter (in sorted order).
- The only difference lies in the fact that SJF is based on the current burst time and is non preemptive, whereas FCFS is based solely on the arrival times.
- The I/O-bound processes have been given higher priorities than the CPU-bound processes.

### Shortest Remaining Time First

- SRTF is essentially a preemptive SJF algorithm.
- To get the next time point at which a new process might be available for consideration, there are 2 priority queues implemented - one sorted in the arrival time and second sorted on the burst time.
- Using these 2 priority queues, we get one schedulable process at a time and the burst time gets exhausted with the same amount as the time duration (that is calculated).

### Priority Scheduling (Preemptive and non-Preemptive)

- Similar to the SRTF implementation, to get the next time point at which a new process might be available for consideration, there are 2 priority queues implemented - one sorted in the arrival time and second sorted on the priorities.
- As the name suggests, in the preemptive variation, we always look at the time instant and select the process available with the highest priority.
- And in the non preemptive variation every schedulable entity runs out its burst time1 and then burst time2.

### Round Robin

- A Round Robin queue is maintained in which processes are enqueued according to the algorithm.
- As the assigned process’ time slice runs out, it is popped from the running queue and pushed into this Round Robin queue.
- As burst_time1 runs out, assuming infinite I/O devices the io_time is handled and then burst_time2 is scheduled again in the same enqueueing into the queue fashion.

### Multi-level queue scheduling

- In our implementation, there are 2 queues - Interactive queue and background queue.
- Interactive queue is assigned a 70% time slice and the background queue is assigned a 30% time slice.
- For example - if we have 10 seconds then we give 7 seconds to Interactive queue process and then 3 seconds to background queue process.

### Multi-level Feedback queue scheduling

- In our implementation, there are 3 queues - first queue, second queue and FCFS queue.
- The first and second queue follow the Round Robin algorithm whereas the last queue follows the First Come First Serve algorithm (FCFS) .
- The time quantum for the first queue is 4 and for the second queue, it is 8 units of time quantum.

### Execution Details

Follow the given commands to run the project.

```sh
pip3 install -r requirements.txt
python3 os_simulation.py
```

### Output

The simulation results into following output:
![Output Image](https://ibb.co/MGSfqzk)

### Inut For processes

- The input times are in ms, so the values are to be taken in ms.

### Question for Round Robin

> In a real OS, the shortest timeslice possible is usually not the best choice. Why not?

Ans: It takes some time to change the context between two tasks. Let's assume that a given system has two runnable tasks. Every context switch will occur in around the same amount of time, say 0.1ms. Each job is given 9.9ms to perform, thus if context switches happen every 10ms, 99% of each 1ms interval is used for task execution and 1% is used for context shifts. Context transitions waste 10% of the time if we increase the frequency to once every millisecond. In the worst case scenario, if we increase again to have a context transition every 0.1 ms, then the entire processor time is spent in context switches, leaving no time for the apps to run.

Therefore, it is ideal to have context transitions as infrequently as feasible for performance. This lengthens the time that can be used to execute applications However, if context shifts happen infrequently enough, there will be a lag before a programme responds to an outside event. This is not an issue for purely computational programmes, but it is an issue for input/output programmes. A network server may take up to one second to respond (or more if there are more than two tasks), an interactive programme may take up to one second to react to a keypress, etc., whereas computational tasks don't waste time when context switches only happen once every second.

A balance between computing performance and reactivity must therefore be struck by the operating system scheduler. I/O-bound jobs are given shorter, more frequent time slices by sophisticated schedulers, whereas computational tasks are given longer, less frequent time slices. These schedulers attempt to identify which tasks are computational and which ones are I/O-bound.
