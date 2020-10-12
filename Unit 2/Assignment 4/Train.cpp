#include "Train.h"

//Creates a Train with an engine and caboose
Train::Train()
{
    engine = new trainCar;
    caboose = new trainCar;

    engine->next = caboose;
    caboose->previous = engine;
}

//Builds a doubly Linked List of trainCar structs from two arrays
void Train::buildTrain(std::string names[], int caps[])
{
    engine->name = names[0];
    engine->capacity = caps[0];
    engine->occupancy = 1;

    caboose->name = names[10];
    caboose->capacity = caps[10];
    caboose->occupancy = 1;

    for(int i = 9; i > 0; i--)
    {
        addCar(names[i], caps[i], 0, engine);
    }
}

//Iterates through and prints all trainCars
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

//Adds passengers two existing trains based on their desination. Creates a new trainCar if capacity is reached
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
}

//Adds a trainCar after car *p. If the trainCar name already exists, indexes the name to distinguish it.
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

    cout << newTrainCar->name << ":" << newTrainCar->capacity << ":" << newTrainCar->occupancy << endl;
}