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
    Train();
    
    void buildTrain(std::string names[], int caps[]);
    void printTrain();
    void addPassengers(std::string name, int numPassengers);
protected:
private:
    trainCar *engine;//head of the linked list
    trainCar *caboose;//tail of the linked list
    int numCarTypes = 9; //number of unique car names, not including engine and caboose
    void addCar(std::string n, int c, int o, trainCar *p);
};

#endif // TRAIN_H