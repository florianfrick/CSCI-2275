#include "priorityQueueHeap.h"
#include <iostream>

priorityQueueHeap::priorityQueueHeap(int capa)
{
    capacity = capa;
    currentSize = 0;
    heap = new heapItem*[capacity];
}

//add to heap, then move to correct position
void priorityQueueHeap::push(heapItem *obj)
{
    if (currentSize == capacity)
    {
        std::cout << "full";
    }
    else
    {
        currentSize++;
        int i = currentSize;
        heap[i] = obj;
        while(i > 1 && !heapItem::oneIsSmallerPriority(heap[i/2], heap[i]) )
        {
            swap(i,i/2); //swaps indexes
            i /= 2;
        }
    }
}

heapItem* priorityQueueHeap::pop()
{
    if(currentSize==0)
    {
        std::cout << "empty";
        return NULL;
    }
    if (currentSize == 1)
    {
        currentSize--;
        return heap[1];
    }

    heapItem* popVal = heap[1];
    heap[1] = heap[currentSize];
    currentSize--;
    minHeapify(1);
    return popVal;
}

void priorityQueueHeap::minHeapify(int i)
{
    int left = 2*i;
    int right = 2*i+1;
    int smallest = i;
    //sorts by priority and treatment
    if(left <= currentSize && heapItem::oneIsSmallerPriority(heap[left], heap[smallest]))
        smallest = left;

    if(right <= currentSize && heapItem::oneIsSmallerPriority(heap[right], heap[smallest]))
        smallest = right;

    if(smallest != i)
    {
        swap(i, smallest); //swaps indexes
        minHeapify(smallest);
    }
}

void priorityQueueHeap::swap(int one, int two)
{
    heapItem* temp = heap[one];
    heap[one] = heap[two];
    heap[two] = temp;
}