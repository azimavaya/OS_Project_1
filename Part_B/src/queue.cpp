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


// dequeue(): removes the process at the front of the queue

PCB* ReadyQueue::dequeue() {

    if (isEmpty())
        return nullptr;

    Node* temp = front;
    PCB* p = temp->process;
    front = front->next;

    if (front == nullptr)
        rear = nullptr;

    delete temp;
    return p;
}


//peekFront(): rturns the process at the front without removing it

PCB* ReadyQueue::peekFront() const {

    if (isEmpty())
        return nullptr;

    return front->process;
}

