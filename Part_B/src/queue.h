#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"
#include <fstream>
using namespace std;

struct Node {
    PCB* process;
    Node* next;
};

class ReadyQueue {
private:
    Node* front; //Pointer to the first node in the queue
    Node* rear; //Pointer to the last node in the queue
