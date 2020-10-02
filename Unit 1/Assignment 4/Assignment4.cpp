#include <iostream>
#include <fstream>
#include <sstream>

#include "Train.cpp"
#include "Train.h"

using namespace std;

int main(int argc, char* argv[])
{
    string names[11] {"The Little Engine That Could", "Gilette", "Oreville", "Keystone", "Addie Camp", "Redfern", "Mystic", "Rochford", "Harney Canyon", "Bluebird", "Red Caboose"};
    int capacities[11] {1,48,40,35,25,20,50,52,40,50,1};

    
    Train train;
    cout << "Added:" << endl;
    train.buildTrain(names, capacities);
    cout << "\n\t--Initial Train--" << endl;
    train.printTrain();
    cout << endl;
    cout << "Added:" <<endl;

    ifstream file;
    file.open(argv[1]);
    string line;
    while(getline(file,line)) //for every line
    {
        string destination;
        int numPassengers;

        stringstream ss(line);
        string partOfLine;
        int i = 0;
        while(getline(ss, partOfLine, ',')) //seperate destination and number of tickets
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
        train.addPassengers(destination, numPassengers); //and add passengers
    }

    cout << "\n \n\t--Final Train--" << endl;
    train.printTrain();

    return 0;
}