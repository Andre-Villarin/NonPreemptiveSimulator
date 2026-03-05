#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * This struct represents a process in the simulator.
 *
 * It contains input attributes (arrival_ns, burst_ns, nice_level)
 * and runtime metrics (waiting_ns, turnaround_ns, response_ns)
 * which is displayed upon completion of the simulated algorithm.  
 * 
 * TODO Revise comment and finalize struct
*/
struct PCB {

    int index;                  // from 1 to X
    int arrival_ns;             // when the process arrives
    int remaining_ns;           // remaining CPU time for this process
    int nice_level;             // priority level range [-20, 20]

    int burst_ns = 0;           // total CPU time taken by process so far
				                // init to 0 at the start
    int waiting_ns = 0;         // time in ready queue
    int turnaround_ns = 0;      // time from arrival to completion
    int response_ns = -1;       // time from arrival to first processing
                                // init to -1 to indicate "not started"
    bool is_completed = false;


    PCB* next;

    PCB() {
        next = nullptr;
    }
};
 
struct ReadyQueue {
    PCB* head;
    PCB* tail;

    ReadyQueue() {
        head = tail = nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void enqueue(PCB* p) {
        p->next = nullptr;

        if (isEmpty()) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
            tail->next = nullptr;
        }
    }

    PCB* dequeue() {
        
        if (isEmpty()) return nullptr;

        PCB* temp = head;
        if (head->next != nullptr) {
            head = head->next;
        } else {
            head = tail = nullptr;
        }
        temp->next = nullptr;
        return temp;
    }
};

struct TestCase {
    /* test case processes (possibly in an array?)
        but it has to be dynamically sized

        eg. PCB *processes[] = new PCB[X]
    */
    PCB *processes; // list of all jobs (independent of ReadyQueue)
    int quantum_ns; // used only by RR
    int numProcesses;
    string algorithm;

    TestCase() {
        processes = nullptr;
        quantum_ns = 0;
    }

    ~TestCase() {
        delete[] processes;
    }
};

/**
    * Parses input from a txt file, and instantiates a TestCase struct.
    * 
    * @param numProcesses: An integer which indicates the number of processes (PCB)
    * @param algorithm: Indicates the algorithm to be run on the TestCase
    * @return A TestCase 't' which has an array of PCB initialized, and other relevant information
*/ 
TestCase parseInput(int numProcesses, string algorithm) {
    TestCase t;
    t.processes = new PCB[numProcesses];

    if (algorithm == "RR") {
        cin >> t.quantum_ns;    // this will assume valid inputs always (ie. Q > 0 always)
    }

    t.algorithm = algorithm;
    t.numProcesses = numProcesses;         

    for(int i = 0; i < t.numProcesses; i++) { // set values of processes
        PCB &process = t.processes[i];
        process.index = i + 1;       
        cin >> process.arrival_ns;
        cin >> process.remaining_ns;
        cin >> process.nice_level;
    }

    return t;
}

/**
    * Finds the unfinished process with the earliest arrival time, or in the
    * event of a tie, the process with the lower index.
    * 
    * @param t: A TestCase containing the processes
    * @param current_time_ns: The current time of the CPU
    * @return A PCB* 'p' which references the best process given 
    * the FCFS heuristic
*/ 
PCB* selectFCFS(TestCase &t, int current_time_ns) {
    PCB* best = nullptr;

    for (int i = 0; i < t.numProcesses; i++) {
        PCB &p = t.processes[i];

        // case 1: p is completed or has not arrived yet
        if (p.is_completed || p.arrival_ns > current_time_ns)
            continue;

        // case 2:
        if (best == nullptr ||
            p.arrival_ns < best->arrival_ns ||
            (p.arrival_ns == best->arrival_ns && p.index < best->index)) {
            
            best = &p;
        }
    }

    return best;
}

/**
    * Finds the unfinished process with the shortest remaining_ns, or in the
    * event of a tie, the process with the earlier arrival time, and lower 
    * index. May also return nullptr if no process has arrived yet at all 
    * when t = current_time_ns
    * 
    * @param t: A TestCase containing the processes
    * @param current_time_ns: The current time of the CPU
    * @return A PCB* 'p' which references the best process given 
    * the SJF heuristic
*/ 
PCB* selectSJF(TestCase &t, int current_time_ns) {
    PCB* best = nullptr;

    for (int i = 0; i < t.numProcesses; i++) {
        PCB &p = t.processes[i];

        // case 1: p is completed or takes longer than 'best'
        if (p.is_completed || p.arrival_ns > current_time_ns)
            continue;
            
        // case 2: no 'best' set yet
        if (best == nullptr ||
            p.remaining_ns < best->remaining_ns) {
            best = &p;
            continue;
        }
        
        // case 3: tie
        if (best->remaining_ns == p.remaining_ns) {
            if (p.arrival_ns < best->arrival_ns) {
                best = &p;
                continue;
            }
            if (p.index < best->index) best = &p;
            else continue;
        }
    }

    return best;
}

int findNextArrival(TestCase &t) {
    int min_arrival_ns;
    PCB* best = nullptr;

    for (int i = 0; i < t.numProcesses; i++) {
        PCB &p = t.processes[i];

        if (p.is_completed || p.arrival_ns == min_arrival_ns)
            continue;

        if (best == nullptr || p.arrival_ns < best->arrival_ns) {
            best = &p;
            min_arrival_ns = best->arrival_ns;
        }
    }

    return min_arrival_ns;
}

void printProcesses(TestCase &t, string query) {
    int data;
    for(int i = 0; i < t.numProcesses; i++) {
        if (query == "w") data = t.processes[i].waiting_ns;
        else if (query == "t") data = t.processes[i].turnaround_ns;
        else if (query == "r") data = t.processes[i].response_ns;
        cout << " Process " << t.processes[i].index << ": " << data << "ns " << endl;    
    }
}

void printOutput(TestCase &t, int current_time_ns) {
    // statistics tracking and computing
    int total_time = current_time_ns; // time once out of the while loop, meaning all processes are done
    int sum_b = 0; // total burst
    double sum_w = 0, sum_ta = 0, sum_r = 0; // wait, turnaround, and response time totals

    for (int i = 0; i < t.numProcesses; i++) {
        sum_b += t.processes[i].burst_ns;
        sum_w += t.processes[i].waiting_ns;
        sum_ta += t.processes[i].turnaround_ns;
        sum_r += t.processes[i].response_ns;
    }

    double idle_time = total_time - sum_b;

    // compute other statistics
    double cpu_util = (double) (total_time-idle_time) / total_time *100.0;
    double throughput = (double) t.numProcesses / total_time;
    double avg_wait = sum_w / t.numProcesses;
    double avg_ta = sum_ta / t.numProcesses;
    double avg_resp = sum_r / t.numProcesses;
    
    cout << "Total time elapsed: " << total_time << "ns" << endl;
    cout << "Total CPU burst time: " << sum_b << "ns" << endl;
    cout << "CPU Utilization: " << cpu_util << "%" << endl;
    cout << "Throughput: " << throughput << " processes/ns" << endl;

    cout << "Waiting times: " << avg_wait << "ns" << endl;
    printProcesses(t, "w");

    cout << "Turnaround times: " << avg_ta << "ns" << endl;
    printProcesses(t, "t");

    cout << "Response times: " << avg_resp << "ns" << endl;
    printProcesses(t, "r");
}

void simulateNonPreemptive(TestCase &t) {
    int system_time_ns = 0;
    int num_processes_completed = 0;

    while (num_processes_completed < t.numProcesses) {
        PCB *bestP = nullptr;
        
        if (t.algorithm == "FCFS") {
            bestP = selectFCFS(t, system_time_ns);
        } else if (t.algorithm == "SJF") {
            bestP = selectSJF(t, system_time_ns);
        }

        if (bestP == nullptr) {
            system_time_ns = findNextArrival(t);
            continue;
        }
        
        // simulate bestP

        if (bestP->response_ns == -1) {
            bestP->response_ns = system_time_ns - bestP->arrival_ns;
        }
        
        cout << system_time_ns << " ";

        system_time_ns += bestP->remaining_ns;

        bestP->burst_ns = bestP->remaining_ns;  // since non-preemptive, burst until complete
        bestP->remaining_ns = 0;
        bestP->is_completed = true;
        bestP->turnaround_ns = system_time_ns - bestP->arrival_ns;
        bestP->waiting_ns = system_time_ns - bestP->arrival_ns - bestP->burst_ns;
        
        cout << bestP->index << " " << bestP->burst_ns << "X " << endl;
        num_processes_completed++;
    }

    printOutput(t, system_time_ns);

}


/**
    * Takes a TestCase 't' and dispatches it to the appropriate algorithm function
    * 
    * @param t: The TestCase containing the array 'processes'
    * @return A formatted string containing the scheduling results and Gantt
*/ 
void simulateAlgorithm(TestCase &t) {
    if (t.algorithm == "FCFS" || t.algorithm == "SJF") {
        simulateNonPreemptive(t);
    }
}


int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        int numProcesses;
        string algorithm;
        cin >> numProcesses >> algorithm;
        TestCase t = parseInput(numProcesses, algorithm);
        cout << i << " " << algorithm << endl;
        simulateAlgorithm(t);
    }
    return 0;
}