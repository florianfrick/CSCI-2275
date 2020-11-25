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

bool readFile(std::string filename, vector<heapItem*> patientData)
{
    ifstream inStream; // stream for reading in file
    inStream.open(filename); // open the file

    // throw an error if we couldn't open the file
    if (!inStream)
    {
        cout << "Error: Could not open file for reading" << endl;
        return false;
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

        cout << name << " " << priority << " " << treatment << endl;
        heapItem *obj = new heapItem(name, stoi(priority), stoi(treatment)); //create new patient
        patientData.push_back(obj); //add patient to vector
        i++;
    }
    inStream.close();// close the file
    return true;
}

long calculateMean(long times[], int size)
{
    long total;
    for(int i = 0; i < size; i++)
    {
        total+=times[i];
    }
    return total/size;
}

long calculateSD(long times[], const int size, long mean)
{
    long *difs = new long[size];
    for(int i = 0; i < size; i++)
    {
        difs[i] = pow((times[i]-mean), 2);
    }
    return sqrt(calculateMean(difs, size));
}

bool buildRemove(vector<heapItem*> patientData, const int size)
{
    priorityQueueHeap *heap = new priorityQueueHeap(size);
    priorityQueueLL *ll = new priorityQueueLL();
    std::priority_queue<heapItem*> *pq;

    long *heapTimes = new long[size];
    long *llTimes = new long[size];
    long *pqTimes = new long[size];
    long startTime;
    long endTime;
    //adding items
    for(int i = 0; i < size; i++)
    {
        

        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        heap->push(patientData[i]);
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        heapTimes[i] = endTime-startTime;

        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        LLNode *obj = new LLNode(patientData[i]->name, patientData[i]->priority, patientData[i]->treatment, NULL, NULL);
        ll->insertWord(obj);
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        llTimes[i] = endTime-startTime;

        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        pq->push(patientData[i]);
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        pqTimes[i] = endTime-startTime;

        long heapMean = calculateMean(heapTimes, size);
        long heapSD = calculateSD(heapTimes, size, heapMean);
        
        long llMean = calculateMean(llTimes, size);
        long llSD = calculateSD(llTimes, size, llMean);
        
        long pqMean = calculateMean(pqTimes, size);
        long pqSD = calculateSD(pqTimes, size, pqMean);

        std::cout << "Size: " << size << "\nAdd Times" << std::endl;
        std::cout << "Heap Mean\t" << heapMean << std::endl;
        std::cout << "Heap SD\t" << heapSD << std::endl;
        std::cout << "LL Mean\t" << llMean << std::endl;
        std::cout << "LL SD\t" << llSD << std::endl;
        std::cout << "Built-in Mean\t" << pqMean << std::endl;
        std::cout << "Built-in SD\t" << pqSD << std::endl;
    }

    //removing items
    for(int i = 0; i < size; i++)
    {
        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        heap->pop();
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        heapTimes[i] = endTime-startTime;

        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        ll->pop();
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        llTimes[i] = endTime-startTime;

        startTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        pq->pop();
        endTime = chrono::duration_cast<std::chrono::milliseconds>( chrono::system_clock::now().time_since_epoch() ).count();
        pqTimes[i] = endTime-startTime;

        long heapMean = calculateMean(heapTimes, size);
        long heapSD = calculateSD(heapTimes, size, heapMean);
        
        long llMean = calculateMean(llTimes, size);
        long llSD = calculateSD(llTimes, size, llMean);
        
        long pqMean = calculateMean(pqTimes, size);
        long pqSD = calculateSD(pqTimes, size, pqMean);

        std::cout << "\nRemove Times" << std::endl;
        std::cout << "Heap Mean\t" << heapMean << std::endl;
        std::cout << "Heap SD\t" << heapSD << std::endl;
        std::cout << "LL Mean\t" << llMean << std::endl;
        std::cout << "LL SD\t" << llSD << std::endl;
        std::cout << "Built-in Mean\t" << pqMean << std::endl;
        std::cout << "Built-in SD\t" << pqSD << std::endl;
    }
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
    readFile(argv[1], patientData);

    for(int i = 100; i < 880; i+=100)
    {
        //adds and removes from each priority queue
        //buildRemove(patientData, min(i,880));
    }

}
