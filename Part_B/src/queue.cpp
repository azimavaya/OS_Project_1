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

// Returns true if queue is empty

bool ReadyQueue::isEmpty() const {
    return front == nullptr;
}


//enqueue(): adds a process to the end of the queue
void ReadyQueue::enqueue(PCB* p) {

    Node* newNode = new Node;
    newNode->process = p;
    newNode->next = nullptr;

    if (rear == nullptr) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}
