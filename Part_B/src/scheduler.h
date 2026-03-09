#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "pcb.h"
#include "queue.h"
#include <fstream>
using namespace std;

string stateToString(State s);
int loadProcesses(const string& filename, PCB*& processes);
void resetProcesses(PCB* processes, int count);
bool allTerminated(PCB* processes, int count);
void admitArrivals(PCB* processes, int count, int currentTime, ReadyQueue& ready);
void printTrace(ofstream& out, int currentTime, PCB* running, const ReadyQueue& ready);
void printGanttChart(ofstream& out, string gantt[], int length);
void simulateFCFS(PCB* processes, int count, const string& outputFile);
void simulatePriority(PCB* processes, int count, const string& outputFile);
void simulateSRTF(PCB* processes, int count, const string& outputFile);
void simulateRR(PCB* processes, int count, const string& outputFile, int quantum);

#endif
