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

    simulateSRTF(processes, count, "output_srtf.txt");

    cout << "SRTF simulation complete. Check output_srtf.txt" << endl;

    delete[] processes;
    return 0;
}
