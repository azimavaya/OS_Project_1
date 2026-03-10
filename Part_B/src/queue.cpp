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

//rmShortestRemain(): Used for SRTF scheduling

PCB* ReadyQueue::rmShortestRemain() {

    if (isEmpty())
        return nullptr;

    Node* curr = front;
    Node* prev = nullptr;
    Node* best = front;
    Node* bestPrev = nullptr;

    while (curr != nullptr) {

        if (curr->process->remaining < best->process->remaining) {
            best = curr;
            bestPrev = prev;
        }

        prev = curr;
        curr = curr->next;
    }

    if (bestPrev == nullptr) {
        front = front->next;

        if (front == nullptr)
            rear = nullptr;
    }
    else {
        bestPrev->next = best->next;

        if (best == rear)
            rear = bestPrev;
    }

    PCB* p = best->process;
    delete best;
    return p;
}

//rmHighestPriority(): used for Priority scheduling

PCB* ReadyQueue::rmHighestPriority() {

    if (isEmpty())
        return nullptr;

    Node* curr = front;
    Node* prev = nullptr;
    Node* best = front;
    Node* bestPrev = nullptr;

    while (curr != nullptr) {

        if (curr->process->priority < best->process->priority) {
            best = curr;
            bestPrev = prev;
        }

        prev = curr;
        curr = curr->next;
    }

    if (bestPrev == nullptr) {

        front = front->next;

        if (front == nullptr)
            rear = nullptr;
    }
    else {

        bestPrev->next = best->next;

        if (best == rear)
            rear = bestPrev;
    }

    PCB* p = best->process;
    delete best;
    return p;
}

// Return the ready process with the smallest remaining time without removing it 
PCB* ReadyQueue::peekShortestRemain() const {
    if (isEmpty()) {
        return nullptr;
    }

    Node* curr = front;
    PCB* shortest = front->process;

    while (curr != nullptr) {
        if (curr->process->remaining < shortest->remaining) {
            shortest = curr->process;
        }
        curr = curr->next;
    }

    return shortest;
}

// printQueue(): prints all processes waiting in the ready queue

void ReadyQueue::printQueue(ofstream& out) const {

    Node* curr = front;
    while (curr != nullptr) {

        PCB* p = curr->process;

        out << "PID=" << p->pid
            << " Arr=" << p->arrival
            << " Burst=" << p->burst
            << " Rem=" << p->remaining
            << " Prio=" << p->priority
            << " State=" << stateToString(p->state)
            << endl;

        curr = curr->next;
    }
}
