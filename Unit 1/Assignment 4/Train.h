//
//  Assignment4.h
//  Assignment4
//
//

#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>

using namespace std;

struct trainCar{
    std::string name;
    int capacity;
    int occupancy;
    trainCar *next;
    trainCar *previous;
    trainCar(){}; // default constructor

    string namePart() //separates the name from any underscore/number
    {
        int u;
        size_t t = this->name.find('_'); //t=npos if no underscore
        t == string::npos ? u = this->name.size() : u = t ;
        return this->name.substr(0,u);
    }
    
    trainCar(std::string initName, int cap, int occup, trainCar *initNext, trainCar *initPrevious)
    {
        name = initName;
        capacity = cap;
        occupancy = occup;
        next = initNext;
        previous = initPrevious;
    }

};
class Train
{
public:
    Train()
    {
        engine = new trainCar;
        caboose = new trainCar;

        engine->next = caboose;
        caboose->previous = engine;
    }
    
    void buildTrain(std::string names[], int caps[])
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

    void printTrain()
    {
        trainCar *temp = engine;
        while(temp != NULL)
        {
            cout << temp->name << ":"<< temp->capacity << ":" << temp->occupancy << endl;
            temp = temp->next;
        }
        delete temp;
    }

    void addPassengers(std::string name, int numPassengers)
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
protected:
private:
    trainCar *engine;//head of the linked list
    trainCar *caboose;//tail of the linked list
    int numCarTypes = 9; //number of unique car names, not including engine and caboose

    void addCar(std::string n, int c, int o, trainCar *p)
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


        cout << "\t" << newTrainCar->name << ":" << newTrainCar->capacity << ":" << newTrainCar->occupancy << endl;
    }
};

#endif // TRAIN_H


