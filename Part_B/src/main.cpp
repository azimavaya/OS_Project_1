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

    cout << "FCFS simulation complete. Check output_fcfs.txt" << endl;

    delete[] processes;
    return 0;
}
