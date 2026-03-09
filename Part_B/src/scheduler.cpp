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

int loadProcesses(const string& filename, PCB*& processes) {
    processes = nullptr;
    return 0;
}

void resetProcesses(PCB* processes, int count) {
}

bool allTerminated(PCB* processes, int count) {
    return true;
}

void admitArrivals(PCB* processes, int count, int currentTime, ReadyQueue& ready) {
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
