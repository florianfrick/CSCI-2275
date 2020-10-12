#include "Train.h"
#include <string>
#include <iostream>

using namespace std;

Train::Train()
{
    engine = new trainCar;
    caboose = new trainCar;

    engine->next = caboose;
    caboose->previous = engine;

    trainQueue = new Queue(10); //queue size
}

void Train::buildTrain(std::string names[], int caps[])
{
    engine->name = "The Little Engine That Could";
    engine->capacity = 1;
    engine->occupancy = 1;

    caboose->name = "Red Caboose";
    caboose->capacity = 1;
    caboose->occupancy = 1;

    for(int i = 8; i >= 0; i--)
    {
        addCar(names[i], caps[i], 0, engine);
    }
}

void Train::printTrain()
{
    trainCar *temp = engine;
    while(temp != NULL)
    {
        cout << temp->name << ":"<< temp->capacity << ":" << temp->occupancy << endl;
        temp = temp->next;
    }
    delete temp;
}

bool Train::enqueuePassengers(carPassengers cp)
{
    return trainQueue->enqueue(cp);
}

bool Train::dequeuePassengers()
{
    if(trainQueue->queueIsEmpty())
    {
        return false;
    }
    carPassengers cp = trainQueue->dequeue();
    addPassengers(cp.carName, cp.passengers);
    return true;
}

void Train::removePassengers(std::string carName, int numPassengers)
{
    trainCar *temp = engine;
    while(temp != NULL && temp->namePart() != carName)
    {
        temp = temp->next;
    }

    int newOccupancy = temp->occupancy - numPassengers;
    if(numPassengers > temp->capacity)//redundant?
    {
        //delete car from train
        temp->capacity = 0;
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
    }
    else if(newOccupancy > 0)
    {
        //car still has occupancy
        temp->occupancy = newOccupancy;
    }
    else
    {
        //delete car from train
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
    }
}


void Train::addCar(std::string n, int c, int o, trainCar *p)
{
    trainCar *newTrainCar = new trainCar;

    int u;
    size_t t = p->name.find('_');
    t == string::npos ? u = p->name.size() : u = t;

    if(t == string::npos) //has no underscore
    {
        if(p->name == n) //exact same, first new cart
        {
            newTrainCar->name = n + "_" + to_string(1);
        }
        else
        {
            newTrainCar->name = n; //set name
        }
    }
    else //has underscore
    {           
        newTrainCar->name = n + "_" + to_string(stoi(p->name.substr(u+1))+1);
    }
    
    
    newTrainCar->capacity = c; //set capacity
    
    if(o > c) //occupancy is greater than capacity
    {
        addCar(n, c, o-c, p); //make a new car with occupancy o-c
        newTrainCar->occupancy = c; //set occupancy as max
    }
    else
    {
        newTrainCar->occupancy = o; //set occupancy as o
    }

    newTrainCar->next = p->next; //set next
    p->next = newTrainCar; //point forwards to new traincar
    newTrainCar->previous = p; //set prev
    newTrainCar->next->previous = newTrainCar; //point backwards to new traincar

    cout << "\t Added: " << newTrainCar->name << ":" << newTrainCar->capacity << ":" << newTrainCar->occupancy << endl;
}

void Train::addPassengers(std::string name, int numPassengers)
{
    trainCar *temp = caboose;
    while(temp != NULL && temp->namePart() != name) //temp finds cart to add passengers to
    {
        temp = temp->previous;
    }
    
    int currentOccupancy = temp->occupancy;
    int capacity = temp->capacity;
    if(capacity >= currentOccupancy + numPassengers)
    {
        temp->occupancy = currentOccupancy + numPassengers; //if the capacity is large enough for all new passengers, it just adds to the occupancy
    }
    else //new car necessary
    {
        int excessOccupancy = (currentOccupancy+numPassengers) - temp->capacity;
        temp->occupancy = capacity; //fills existing car

        addCar(name, capacity, excessOccupancy, temp);
    }
    delete temp;
}

Queue* Train::getQueue()
{
    return Train::trainQueue;
}

trainCar* Train::getEngine()
{
    return Train::engine;
}

trainCar* Train::getCaboose()
{
    return Train::caboose;
}
