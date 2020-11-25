#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>

struct heapItem
{
    std::string name;
    int priority;
    int treatment;

    heapItem(std::string n, int p, int t)
    {
        name = n;
        priority = p;
        treatment = t;
    }
};

class priorityQueueHeap
{
    public:
        priorityQueueHeap(int capacity);
        void push(heapItem *obj);
        heapItem* pop();
        void printHeap();
    private:
        heapItem *heap;
        int capacity;
        int currentSize;
        void minHeapify(int i);
        void swap(int one, int two);
};

#endif // HEAP_H
