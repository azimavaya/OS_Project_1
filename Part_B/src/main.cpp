#include "scheduler.h"
#include <iostream>
using namespace std;

int main() {
   PCB* processes = nullptr;
    int count = loadProcesses("input.txt", processes);

    if (count == 0) {
        cout << "Failed to load." << endl;
        return 1;
    }
    cout << "Loaded " << count << " processes:" << endl;

    for (int i = 0; i < count; i++) {
        cout << "PID=" << processes[i].pid
             << " Arr=" << processes[i].arrival
             << " Burst=" << processes[i].burst
             << " Rem=" << processes[i].remaining
             << " Prio=" << processes[i].priority
             << " State=" << stateToString(processes[i].state)
             << endl;
    }

    delete[] processes;
    return 0;
}
