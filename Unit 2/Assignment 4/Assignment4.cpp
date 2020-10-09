#include <iostream>
#include <fstream>
#include <sstream>

#include "Train.h"

using namespace std;

int main(int argc, char* argv[])
{
    string names[11] {"The Little Engine That Could", "Gilette", "Oreville", "Keystone", "Addie Camp", "Redfern", "Mystic", "Rochford", "Harney Canyon", "Bluebird", "Red Caboose"};
    int capacities[11] {1,48,40,35,25,20,50,52,40,50,1};


    Train train;
    cout << "\tAdded:" << endl;
    train.buildTrain(names, capacities); //builds initial train
    cout << "\n\t--Initial Train--" << endl;
    train.printTrain(); //prints train
    cout << "\n\tAdded:" <<endl;

    //For every line, separates destination and tickets, then adds passengers 
    ifstream file;
    file.open(argv[1]);
    string line;
    while(getline(file,line)) //Loops through every line
    {
        string destination;
        int numPassengers;

        stringstream ss(line);
        string partOfLine;
        int i = 0;
        while(getline(ss, partOfLine, ','))//Separates destination and tickets
        {
            ss.ignore();
            if(i == 0)
            {
                destination = partOfLine;
            }
            else
            {
                numPassengers = stoi(partOfLine);
            }
            i++;
        }
        train.addPassengers(destination, numPassengers); //Adds passengers
    }

    cout << "\n \n\t--Final Train--" << endl;
    train.printTrain(); //prints final train

    return 0;
}