#include "queue.h"

//Constructor: initializes an empty queue
ReadyQueue::ReadyQueue() {
    front = nullptr;
    rear = nullptr;
}


//Destructor: rremoves all nodes from the queue

ReadyQueue::~ReadyQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}
