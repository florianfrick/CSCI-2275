#include "priorityQueueLL.h"
#include "priorityQueueHeap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <chrono>
#include <math.h>

using namespace std;

vector<heapItem*> readFile(std::string filename)
{
    vector<heapItem*> *patientData = new vector<heapItem*>();

    ifstream inStream; // stream for reading in file
    inStream.open(filename); // open the file

    // throw an error if we couldn't open the file
    if (!inStream)
    {
        cout << "Error: Could not open file for reading" << endl;
        return *patientData;
    }
    // loop until the end of the file
    int i = 0;
    string line;
    getline(inStream, line);//ignore first line
    while (getline(inStream, line)) // reads every line
    {
        stringstream ss(line); //stores line
        string name;
        string priority;
        string  treatment;
        getline(ss, name, ',');
        getline(ss, priority, ',');
        getline(ss, treatment, ',');

        heapItem *obj = new heapItem(name, stoi(priority), stoi(treatment)); //create new patient
        patientData->push_back(obj); //add patient to vector
        i++;
    }
    inStream.close();// close the file
    return *patientData;
}

//calculates mean of array times[]
long calculateMean(long times[], long size)
{
    long total = 0;
    for(int i = 0; i < size; i++)
    {
        total+=times[i];
    }
    return total/size;
}

//calculates standard deviation of array times[] using given mean
long calculateSD(long times[], long size, long mean)
{
    long *difs = new long[size];
    for(int i = 0; i < size; i++)
    {
        difs[i] = pow((times[i]-mean), 2);
    }
    return sqrt(calculateMean(difs, size));
}

//adds and removes 'size' number of items from my heap PQ 100 times and outputs mean and standard deviation
bool heapAddRemove(vector<heapItem*> patientData, int size)
{
    priorityQueueHeap *heap = new priorityQueueHeap(size);
    long *heapTimes = new long[size];

    long startTime = 0;
    long endTime = 0;

    for(int j = 0; j < 100; j++)
    {
        startTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        //adding items
        for(int i = 0; i < size; i++)
        {
            heap->push(patientData[i]);
        }

        //removing items
        for(int i = 0; i < size; i++)
        {
            heap->pop();
        }

        endTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        heapTimes[j] = endTime-startTime;
    }

    long heapMean = calculateMean(heapTimes, 100);
    long heapSD = calculateSD(heapTimes, 100, heapMean);

    std::cout << "Heap Mean," << heapMean << std::endl;
    std::cout << "Heap SD," << heapSD << std::endl;
    std::cout << std::endl;
    return true;
}

//adds and removes 'size' number of items from my linked list PQ 100 times and outputs mean and standard deviation
bool llAddRemove(vector<heapItem*> patientData, int size)
{
    priorityQueueLL ll;
    long *llTimes = new long[size];

    long startTime;
    long endTime;

    for(int j = 0; j < 100; j++)
    {
        startTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        //adding items
        for(int i = 0; i < size; i++)
        {
            ll.insertWord(patientData[i]->name, patientData[i]->priority, patientData[i]->treatment);
        }
        //removing items
        for(int i = 0; i < size; i++)
        {
            LLNode *popped = ll.pop();
        }
        endTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        llTimes[j] = endTime-startTime;
    }

    long llMean = calculateMean(llTimes, 100);
    long llSD = calculateSD(llTimes, 100, llMean);

    std::cout << "LL Mean," << llMean << std::endl;
    std::cout << "LL SD," << llSD << std::endl;
    std::cout << std::endl;
    return true;
}

//adds and removes 'size' number of items from the STD PQ 100 times and outputs mean and standard deviation
bool STDAddRemove(vector<heapItem*> patientData, int size)
{
    std::priority_queue<heapItem> stdPQ;
    long *stdTimes = new long[size];
    long startTime;
    long endTime;

    for(int j = 0; j < 100; j++)
    {
        startTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        //adding items
        for(int i = 0; i < size; i++)
        {
            heapItem currentItem = *patientData[i];
            stdPQ.push(currentItem);
        }
        // removing items
        for(int i = 0; i < size; i++)
        {
            stdPQ.pop();        
        }
        endTime = chrono::duration_cast<std::chrono::microseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        long elapsedTime = endTime-startTime;
        stdTimes[j] = elapsedTime;

    }
    
    long stdPQMean = calculateMean(stdTimes, 100);
    long stdPQSD = calculateSD(stdTimes, 100, stdPQMean);

    std::cout << "Built-in Mean," << stdPQMean << std::endl;
    std::cout << "Built-in SD," << stdPQSD << std::endl;
    std::cout << std::endl;
    return true;
}

int main(int argc, char* argv[])
{
    // verify we have the correct number of parameters, else throw error msg & return
    if (argc < 2)
    {
        cout << "Usage: Assignment6Solution <inputfilename.txt>" << endl;
        return 0;
    }

    std::vector<heapItem*> patientData;
    patientData = readFile(argv[1]);

    for(int i = 100; i <= 900; i+=100)
    {
        //adds and removes from each priority queue from sizes of 100 to 880
        std::cout << "Size: " << min(i,880) << std::endl;
        heapAddRemove(patientData, min(i,880));
        llAddRemove(patientData,min(i,880));
        STDAddRemove(patientData, min(i,880));
    }

}
