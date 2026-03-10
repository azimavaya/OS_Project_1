#include "scheduler.h"
#include <iostream>
using namespace std;

int main() {
    PCB* processes = nullptr;
    int count = loadProcesses("input.txt", processes);

    if (count == 0) {
        cout << "Failed to load processes." << endl;
        return 1;
    }

    simulateFCFS(processes, count, "output_fcfs.txt");

    resetProcesses(processes, count);
    simulatePriority(processes, count, "output_priority.txt");

    resetProcesses(processes, count);
    simulateSRTF(processes, count, "output_srtf.txt");

    resetProcesses(processes, count);
    simulateRR(processes, count, "output_rr.txt", 2);

    cout << "All scheduling simulations completed." << endl;
    cout << "Generated files:" << endl;
    cout << "  output_fcfs.txt" << endl;
    cout << "  output_priority.txt" << endl;
    cout << "  output_srtf.txt" << endl;
    cout << "  output_rr.txt" << endl;

    delete[] processes;
    return 0;
}
