#ifndef HEAP_H
#define HEAP_H

#include<vector>
#include<iostream>

class heapItem
{
    public:
        std::string name;
        int priority;
        int treatment;

        //constructor
        heapItem(std::string name, int priority, int treatment)
            :name(name), priority(priority),treatment(treatment)
        {}

        //comparison method for two items using priority and treatment
        static bool oneIsSmallerPriority(heapItem *one, heapItem *two)
        {
            if(one->priority < two->priority)
            {
                return true;
            }
            else if(one->priority == two->priority)
            {
                if(one->treatment < two->treatment)
                {
                    return true;
                }
                return false;
            }
            else
            {
                return false;
            }
        }

        //overloaded operator< function so that the STD priority queue can use heapItems. Same functionality as oneIsSmallerPriority()
        bool operator<(const heapItem& two) const
        {
            std::cout.flush();
            if(this->priority < two.priority)
            {
                return true;
            }
            else if(this->priority == two.priority)
            {
                if(this->treatment < two.treatment)
                {
                    return true;
                }
                return false;
            }
            else
            {
                return false;
            }
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
        heapItem** heap; //array of pointers to heapItems
        int capacity;
        int currentSize;
        void minHeapify(int i);
        void swap(int one, int two);
};

#endif // HEAP_H
