#include "scheduler.h"
#include <iostream>
#include <fstream>
using namespace std;

string stateToString(State s) {
    switch (s) {
        case NEW: return "NEW";
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case TERMINATED: return "TERMINATED";
        default: return "UNKNOWN";
    }
}

// Load processes from input file into a dynamic PCB aray 
int loadProcesses(const string& filename, PCB*& processes) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: could not open input file." << endl;
        processes = nullptr;
        return 0;
    }
string header;
    getline(inFile, header);  // skip header

    int count = 0;
    string pid;
    int arrival, burst, priority;

    while (inFile >> pid >> arrival >> burst >> priority) {
        count++;
    }

    inFile.close();

    processes = new PCB[count];

    inFile.open(filename);
    getline(inFile, header);  // skipp header again

    for (int i = 0; i < count; i++) {
        inFile >> processes[i].pid
               >> processes[i].arrival
               >> processes[i].burst
               >> processes[i].priority;

        processes[i].remaining = processes[i].burst;
        processes[i].state = NEW;
        processes[i].startTime = -1;
        processes[i].completionTime = -1;
    }

    inFile.close();
    return count;
}


// Reset PCB fields so another scheduling algorithm can run 
void resetProcesses(PCB* processes, int count) {
    for (int i = 0; i < count; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].state = NEW;
        processes[i].startTime = -1;
        processes[i].completionTime = -1;
    }
}
// check if all processes finished execution 
bool allTerminated(PCB* processes, int count) {
    for (int i = 0; i < count; i++) {
        if (processes[i].state != TERMINATED) {
            return false;
        }
    }
    return true;
}
// Move newly arrived processes from new to ready 
void admitArrivals(PCB* processes, int count, int currentTime, ReadyQueue& ready) {
    for (int i = 0; i < count; i++) {
        if (processes[i].state == NEW && processes[i].arrival == currentTime) {
            processes[i].state = READY;
            ready.enqueue(&processes[i]);
        }
    }
}

// Print system state  
void printTrace(ofstream& out, int currentTime, PCB* running, const ReadyQueue& ready) {
    out << "Time " << currentTime << ":" << endl;
    out << "RUNNING:" << endl;

    if (running == nullptr) {
        out << "IDLE" << endl;
    } else {
        out << "PID=" << running->pid
            << " Arr=" << running->arrival
            << " Burst=" << running->burst
            << " Rem=" << running->remaining
            << " Prio=" << running->priority
            << " State=" << stateToString(running->state)
            << endl;
    }

    out << "READY:" << endl;
    ready.printQueue(out);
    out << endl;
}

// Print a Gantt chart 
void printGanttChart(ofstream& out, string gantt[], int length) {
    out << "Gantt Chart:" << endl;

    for (int i = 0; i < length; i++) {
        out << "| " << gantt[i] << " ";
    }
    out << "|" << endl;

    for (int i = 0; i <= length; i++) {
        out << i;
        if (i < 10) {
            out << "     ";
        } else {
            out << "    ";
        }
    }
    out << endl;
}
// first come first serve scheduling 
void simulateFCFS(PCB* processes, int count, const string& outputFile) {
    ofstream out(outputFile);

    if (!out.is_open()) {
        cout << "Error: could not open file " << outputFile << endl;
        return;
    }

    ReadyQueue ready;
    PCB* running = nullptr;
    int currentTime = 0;
    string* gantt = new string[1000];
    int ganttLength = 0;

    out << "FCFS Scheduling Trace" << endl << endl;

    while (!allTerminated(processes, count)) {
        admitArrivals(processes, count, currentTime, ready);

        if (running == nullptr && !ready.isEmpty()) {
            running = ready.dequeue();
            running->state = RUNNING;

            if (running->startTime == -1) {
                running->startTime = currentTime;
            }
        }

        if (running != nullptr) {
            running->remaining--;
            gantt[ganttLength] = running->pid;
        } else {
            gantt[ganttLength] = "IDLE";
        }
        ganttLength++;

        printTrace(out, currentTime, running, ready);

        if (running != nullptr && running->remaining == 0) {
            running->completionTime = currentTime + 1;
            running->state = TERMINATED;
            running = nullptr;
        }

        currentTime++;
    }

    out << endl;
    printGanttChart(out, gantt, ganttLength);

    delete[] gantt;
    out.close();
}

// Priority scheduling 
void simulatePriority(PCB* processes, int count, const string& outputFile) {
    ofstream out(outputFile);

    if (!out.is_open()) {
        cout << "Error: could not open file " << outputFile << endl;
        return;
    }

    ReadyQueue ready;
    PCB* running = nullptr;
    int currentTime = 0;

    string* gantt = new string[1000];
    int ganttLength = 0;

    out << "Priority Scheduling Trace" << endl << endl;

    while (!allTerminated(processes, count)) {
        admitArrivals(processes, count, currentTime, ready);
        if (running == nullptr && !ready.isEmpty()) {
            running = ready.rmHighestPriority();
            running->state = RUNNING;

            if (running->startTime == -1) {
                running->startTime = currentTime;
            }
        }
        if (running != nullptr) {
            running->remaining--;
            gantt[ganttLength] = running->pid;
        } else {
            gantt[ganttLength] = "IDLE";
        }
        ganttLength++;
        printTrace(out, currentTime, running, ready);

        if (running != nullptr && running->remaining == 0) {
            running->completionTime = currentTime + 1;
            running->state = TERMINATED;
            running = nullptr;
        }

        currentTime++;
    }

    out << endl;
    printGanttChart(out, gantt, ganttLength);

    delete[] gantt;
    out.close();
}

//  Shortest Remaining Time First scheduling 
void simulateSRTF(PCB* processes, int count, const string& outputFile) {
    ofstream out(outputFile);

    if (!out.is_open()) {
        cout << "Error: could not open file " << outputFile << endl;
        return;
    }

    ReadyQueue ready;
    PCB* running = nullptr;
    int currentTime = 0;

    string* gantt = new string[1000];
    int ganttLength = 0;

    out << "SRTF Scheduling Trace" << endl << endl;

    while (!allTerminated(processes, count)) {
        admitArrivals(processes, count, currentTime, ready);

        
        if (running == nullptr && !ready.isEmpty()) {
            running = ready.rmShortestRemain();
            running->state = RUNNING;

            if (running->startTime == -1) {
                running->startTime = currentTime;
            }
        }

        else if (running != nullptr && !ready.isEmpty()) {
            PCB* shortestReady = ready.peekShortestRemain();

            if (shortestReady != nullptr &&
                shortestReady->remaining < running->remaining) {

                running->state = READY;
                ready.enqueue(running);

                running = ready.rmShortestRemain();
                running->state = RUNNING;

                if (running->startTime == -1) {
                    running->startTime = currentTime;
                }
            }
        }


        if (running != nullptr) {
            running->remaining--;
            gantt[ganttLength] = running->pid;
        } else {
            gantt[ganttLength] = "IDLE";
        }
        ganttLength++;

        printTrace(out, currentTime, running, ready);

        if (running != nullptr && running->remaining == 0) {
            running->completionTime = currentTime + 1;
            running->state = TERMINATED;
            running = nullptr;
        }

        currentTime++;
    }

    out << endl;
    printGanttChart(out, gantt, ganttLength);

    delete[] gantt;
    out.close();
}

void simulateRR(PCB* processes, int count, const string& outputFile, int quantum) {
}
