#ifndef PCB_H
#define PCB_H

#include <string>
using namespace std;

enum State {
    NEW,
    READY,
    RUNNING,
    TERMINATED
};

struct PCB {
    string pid;
    int arrival;
    int burst;
    int remaining;
    int priority;
    State state;
    int startTime;
    int completionTime;
};

string stateToString(State s);

#endif
