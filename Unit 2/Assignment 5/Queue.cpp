#include "Queue.h"
#include <string>

Queue::Queue(int size)
{
    queueSize = size;
    queueHead = -1;
    queueTail = -1;
    queueCount = 0;
    cpQueue = new carPassengers[size];
}

Queue::~Queue()
{
    queueHead = -1;
    queueTail = -1;
    queueCount = 0;
    delete cpQueue;
}

bool Queue::enqueue(carPassengers cp)//add passengers to queue
{
    if(queueIsFull())
    {
        std::cout << "queue is full" << std::endl;
        return false;
    }
    else if(queueIsEmpty())
    {
        cpQueue[0] = cp; //adds first item
        queueHead = 0;
        queueTail = 0;
        queueCount = 1;
    }
    else if(queueSize-1 == queueTail && queueHead != 0)
    {
        cpQueue[0] = cp; //wraps around
        queueTail = 0;
        queueCount++;
    }
    else
    {
        *(cpQueue+queueTail+1) = cp; //adds item at tail
        queueTail++;
        queueCount++;
    }
    std::cout << "\t" << cp.carName << " added to queue" << std::endl;
    return true;
}

carPassengers Queue::dequeue()//add passengers to train
{
    carPassengers removed = cpQueue[queueHead];
    
    if(queueIsEmpty())
    {
        std::cout << "queue is empty" << std::endl;
    }
    else if(queueHead == queueTail)
    {
        //removes last item in queue
        queueHead = -1;
        queueTail = -1;
    }
    else if(queueHead == queueSize-1)
    {
        queueHead = 0; //wraps around
    }
    else
    {
        queueHead ++;//removes item at head
    }
    queueCount--;
    return removed;
}

void Queue::printQueue() //probably good for debug
{
    if(queueIsEmpty())
    {
        std::cout << "Queue Empty" << std::endl;
    }
    else if(queueTail >= queueHead)
    {
        for(int i = queueHead; i <= queueTail; i++)
        {
            std::cout << cpQueue[i].carName << " " << cpQueue[i].passengers << std::endl;
        }
    }
    else
    {
        for(int i = queueHead; i < queueSize; i++)
        {
            std::cout << cpQueue[i].carName << " " << cpQueue[i].passengers << std::endl;
        }
        //wraps around
        for(int i = 0; i <= queueTail; i++)
        {
            std::cout << cpQueue[i].carName << " " << cpQueue[i].passengers << std::endl;
        }
    }
}

bool Queue::queueIsFull() //check when full
{
    if(queueCount == queueSize)
    {
        return true;
    }
    return false;
}

bool Queue::queueIsEmpty() //check when empty
{
    if(queueCount == 0)
    {
        return true;
    }
    return false;   
}
