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

    simulateRR(processes, count, "output_rr.txt", 2);

    cout << "RR simulation complete. Check output_rr.txt" << endl;

    delete[] processes;
    return 0;
}
