#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include<cmath>
using std::ifstream;
#include <cstdlib>

using namespace std;

/* Type Definition */
typedef unsigned long long ull;
typedef long long ll;
typedef long double lld;

/* UUID Queue */
queue<unsigned int> UUID;
unsigned int getUUID() {
    if (!UUID.empty()) {
        unsigned int uid = UUID.front();
        UUID.pop();
        return uid;
    }
    return rand();
}

/* DataTypes */

enum States {
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

struct PCB {
    unsigned int pid;
    string pname;
    bool ptype; /* 0->IO, 1->CPU */
    int priority;
    lld arrival_time;
    lld burst_time1;
    lld io_time;
    lld burst_time2;
    lld completion_time;
    lld turnaround_time;
    lld waiting_time;
    lld response_time;
    States state;

    PCB(string _pname, lld _arrival_time, lld _burst_time1, lld _io_time, lld _burst_time2, lld _priority) {
        pid = getUUID();
        pname = _pname;
        ptype = _pname[0] == 'I' ? 0 : 1;
        priority = _priority;
        arrival_time = _arrival_time;
        burst_time1 = _burst_time1;
        io_time = _io_time;
        burst_time2 = _burst_time2;
        completion_time = INT64_MIN;
        turnaround_time = INT64_MIN;
        waiting_time = INT64_MIN;
        response_time = INT64_MIN;
        state = NEW;
    }

    ~PCB() {
        UUID.push(pid);
    }
};

struct CompareProcess_fcfs {
    bool operator()(PCB *const &p1, PCB *const &p2) {
        if (p1->arrival_time == p2->arrival_time) {
            if (p1->ptype == 0 and p2->ptype == 0) {
                return p1->pid > p2->pid;
            } else if (p1->ptype == 0) {
                return false;
            } else {
                return true;
            }
        }
        return p1->arrival_time > p2->arrival_time;
    }
};
/* Global Queues */
vector<PCB *> processes, org_processes;
unordered_map<int, PCB *> process_map;
unordered_map<int, PCB *> FcfsRunning_map;
unordered_map<unsigned int, lld> IO_start_time;
priority_queue<PCB *, vector<PCB *>, CompareProcess_fcfs> fcfs_Ready_queue;
queue<PCB *> Device_queue;
lld Last_io_UpdationTime = 0;
lld Avg_TAT = 0;
lld Avg_WT = 0;
lld Avg_RT = 0;
/* Utility Functions */
void terminate(PCB *, lld);
void adjust_Device_queue(lld Curr_Time);
vector<PCB *> Fcfs();
void context_switch(PCB *, States);
bool scheduleFcfs();
void getAvg();
void yield(PCB *);
void wake_up(PCB *);
void preempt(PCB *);

int main() {
    for (int i = 0; i < 500; i++) {
        UUID.push(i);
    }
    PCB *IdleProcess1 = new PCB("IIdle1", 0, 0, 0, INT64_MAX, -1);

    int n;
    
   
    string ProcessName;
    lld ArrivalTime, BurstTime1, IOTime, BurstTime2;
    ifstream indata; 

    indata.open("./Input/inp1.txt"); 
    if(!indata) { 
    cerr << "Error: file could not be opened" << endl;
    exit(1);
   }
   indata >> n;
    for (int i = 0; i < n; i++) {
        indata >> ProcessName;
        indata >> ArrivalTime >> BurstTime1 >> IOTime >> BurstTime2;
        PCB *temp = new PCB(ProcessName, ArrivalTime, BurstTime1, IOTime, BurstTime2, 0);
        PCB *temp1 = new PCB(ProcessName, ArrivalTime, BurstTime1, IOTime, BurstTime2, 0);
        org_processes.push_back(temp1);
        processes.push_back(temp);
    }
    indata.close();
    

    Fcfs();
    for (int i = 0; i < processes.size(); i++) {
        org_processes[i]->completion_time = processes[i]->completion_time;
        org_processes[i]->response_time = processes[i]->response_time;
        org_processes[i]->turnaround_time = org_processes[i]->completion_time - org_processes[i]->arrival_time;
        org_processes[i]->waiting_time = org_processes[i]->turnaround_time - (org_processes[i]->burst_time1 + org_processes[i]->burst_time2 + org_processes[i]->io_time);
    }
    getAvg();
        ofstream MyFile("./output/out1.txt");
      MyFile 
         << "Avg_tat: " << Avg_TAT << endl
         << "Avg_Wt: " << Avg_WT << endl
         << "Avg_Rt: " << Avg_RT << endl;
  
    MyFile << "pname  priority   arrival_time  burst_time1  io_time  burst_time2  completion_time  response_time  turnaround_time  waiting_time     state  " << endl;
    for (int i = 0; i < processes.size(); i++) {
        MyFile << org_processes[i]->pname << "\t" << org_processes[i]->priority << "\t\t"
             << org_processes[i]->arrival_time << "\t\t" << org_processes[i]->burst_time1 << "\t"
             << org_processes[i]->io_time << "\t" << org_processes[i]->burst_time2 << "\t\t"
             << org_processes[i]->completion_time << "\t\t" << org_processes[i]->response_time
             << "\t\t" << org_processes[i]->turnaround_time << "\t\t"
             << org_processes[i]->waiting_time << "\t\t" << org_processes[i]->state << "\n";
    }
    

    return 0;
}

void context_switch(PCB *currp, States st) {
    currp->state = st;
}

void terminate(PCB *currp, lld Curr_Time) {
    currp->completion_time = Curr_Time;
    context_switch(currp, TERMINATED);
}

void yield(PCB *pcb) {
    context_switch(pcb, WAITING);
}
void wake_up(PCB *pcb) {
    context_switch(pcb, READY);
}
void preempt(PCB *pcb) {
    context_switch(pcb, READY);
}
void getAvg() {
    for (int i = 0; i < processes.size(); i++) {
        Avg_TAT += org_processes[i]->turnaround_time;
        Avg_WT += org_processes[i]->waiting_time;
        Avg_RT += org_processes[i]->response_time;
    }
    lld n = processes.size();
    Avg_TAT /= n;
    Avg_WT /= n;
    Avg_RT /= n;
    return;
}
// void adjust_Device_queue(lld Curr_Time) {
//     int len = Device_queue.size();
//     int i = 0;
//     while (i < len) {
//         i++;
//         PCB *pcb = Device_queue.front();
//         Device_queue.pop();
//         if (pcb->io_time > (Curr_Time - IO_start_time[pcb->pid])) {
//             Device_queue.push(pcb);
//             continue;
//         } else {
//             lld tempIo_time = pcb->io_time;
//             pcb->io_time = 0;
//             if (pcb->burst_time2 <= 0) {
//                 terminate(pcb, tempIo_time + IO_start_time[pcb->pid]);
//             } else {
//                 wake_up(pcb);
//                 fcfs_Ready_queue.push(pcb);
//             }
//         }
//     }
// }

bool compare_float(lld x, lld y, lld epsilon = 0.01f) {
    if (fabs(x - y) < epsilon)
        return true;  // they are same
    return false;     // they are not same
}

void adjust_Device_queue(lld Curr_Time) {
    int len = Device_queue.size();
    int i = 0;
    while (i < len) {
        i++;
        PCB *pcb = Device_queue.front();
        Device_queue.pop();
        if (pcb->io_time < (Curr_Time - IO_start_time[pcb->pid]) or compare_float(pcb->io_time, Curr_Time - IO_start_time[pcb->pid])) {
            lld tempIo_time = pcb->io_time;
            pcb->io_time = 0;
            if (pcb->burst_time2 <= 0) {
                terminate(pcb, tempIo_time + IO_start_time[pcb->pid]);
            } else {
                wake_up(pcb);
                fcfs_Ready_queue.push(pcb);
            }
        } else {
            Device_queue.push(pcb);
            continue;
        }
    }
}


lld getCurrTime() {
    lld New_Curr_Time = 0;
    int len = Device_queue.size();
    int i = 0;
    PCB *pcb = Device_queue.front();
    New_Curr_Time = (pcb->io_time + IO_start_time[pcb->pid]);
    while (i < len) {
        i++;
        PCB *pcb = Device_queue.front();
        Device_queue.pop();
        if (New_Curr_Time > (pcb->io_time + IO_start_time[pcb->pid])) {
            New_Curr_Time = (pcb->io_time + IO_start_time[pcb->pid]);
        }
        Device_queue.push(pcb);
    }
    return New_Curr_Time;
}
bool scheduleFcfs() {
    // 0 pid is for idle process
    if (FcfsRunning_map.size() == 1 and FcfsRunning_map.find(0) == FcfsRunning_map.end()) {
        return true;
    }
    // If only idle process is present and some other process comes
    if (fcfs_Ready_queue.size() >= 1 and FcfsRunning_map.size() == 1 and FcfsRunning_map.find(0) != FcfsRunning_map.end()) {
        PCB *idlep = FcfsRunning_map[0];
        FcfsRunning_map.erase(0);
        fcfs_Ready_queue.push(idlep);
        context_switch(idlep, READY);

        PCB *currprocess = fcfs_Ready_queue.top();
        fcfs_Ready_queue.pop();
        FcfsRunning_map[currprocess->pid] = currprocess;
        context_switch(currprocess, RUNNING);
        return true;
    }
    // If running queue is empty, schedule any process in pq
    else if (FcfsRunning_map.size() == 0) {
        PCB *currprocess = fcfs_Ready_queue.top();
        fcfs_Ready_queue.pop();
        FcfsRunning_map[currprocess->pid] = currprocess;
        context_switch(currprocess, RUNNING);
        return true;
    }
    return false;
}

vector<PCB *> Fcfs() {
    vector<PCB *> FcfsVect;
    sort(processes.begin(), processes.end(), [](auto &a, auto &b) { return a->arrival_time < b->arrival_time; });
    sort(org_processes.begin(), org_processes.end(), [](auto &a, auto &b) { return a->arrival_time < b->arrival_time; });
    lld Curr_Time = 0;
    bool flag = true;
    for (int i = 0; i < processes.size(); i++) {
        fcfs_Ready_queue.push(processes[i]);
        context_switch(processes[i], NEW);
    }
    while (fcfs_Ready_queue.size() > 0) {
        adjust_Device_queue(Curr_Time);
        PCB *pcb = fcfs_Ready_queue.top();
        if (pcb->response_time == INT64_MIN) {
            pcb->response_time = Curr_Time;
        }
        lld prev_Curr_Time = Curr_Time;
        bool check = scheduleFcfs();
        if (!check && !Device_queue.empty()) {
            Curr_Time = getCurrTime();
            adjust_Device_queue(Curr_Time);
            scheduleFcfs();
        }
        if (flag) {
            Curr_Time = pcb->arrival_time + pcb->burst_time1;
            pcb->burst_time1 = 0;
            if (pcb->io_time > 0) {
                yield(pcb);
                Device_queue.push(pcb);
                IO_start_time[pcb->pid] = Curr_Time;
            } else {
                Curr_Time += pcb->burst_time2;
                pcb->burst_time2 = 0;
                terminate(pcb, Curr_Time);
            }
            flag = false;
        } else {
            if (pcb->burst_time1 > 0) {
                if (pcb->arrival_time < Curr_Time) {
                    Curr_Time += pcb->burst_time1;
                } else {
                    Curr_Time = pcb->arrival_time + pcb->burst_time1;
                }
                pcb->burst_time1 = 0;
                if (pcb->io_time > 0) {
                    yield(pcb);
                    Device_queue.push(pcb);
                    IO_start_time[pcb->pid] = Curr_Time;
                } else {
                    Curr_Time += pcb->burst_time2;
                    pcb->burst_time2 = 0;
                    terminate(pcb, Curr_Time);
                }
            } else {
                if (pcb->arrival_time < Curr_Time) {
                    Curr_Time += pcb->burst_time2;
                } else {
                    Curr_Time = pcb->arrival_time + pcb->burst_time2;
                }
                pcb->burst_time2 = 0;
                terminate(pcb, Curr_Time);
            }
        }
        FcfsRunning_map.erase(pcb->pid);
        FcfsRunning_map.clear();
        if (fcfs_Ready_queue.empty() && !Device_queue.empty()) {
            Curr_Time = getCurrTime();
            adjust_Device_queue(Curr_Time);
        }
    }

    adjust_Device_queue(Curr_Time + 10000000);
    return FcfsVect;
}