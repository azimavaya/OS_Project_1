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

void printTrace(ofstream& out, int currentTime, PCB* running, const ReadyQueue& ready) {
}

void simulateFCFS(PCB* processes, int count, const string& outputFile) {
}

void simulatePriority(PCB* processes, int count, const string& outputFile) {
}

void simulateSRTF(PCB* processes, int count, const string& outputFile) {
}

void simulateRR(PCB* processes, int count, const string& outputFile, int quantum) {
}
