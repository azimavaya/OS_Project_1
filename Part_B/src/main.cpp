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

    simulatePriority(processes, count, "output_priority.txt");

    cout << "Check output_priority.txt" << endl;

    delete[] processes;
    return 0;
}
