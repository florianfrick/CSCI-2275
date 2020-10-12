#include <iostream>
#include <fstream>
#include <sstream>
#include "Train.h"
#include "Queue.h"

using namespace std;

int main(int argc, char *argv[]){
    string names[9] = {"Gilette", "Oreville", "Keystone", "Addie Camp", "Redfern", "Mystic", "Rochford", "Harney Canyon", "Bluebird"};
    int caps[9] = {48, 40, 35, 25, 20, 50, 52, 40, 50};
    Train myTrain;
    myTrain.buildTrain(names, caps);
    myTrain.printTrain();
    ifstream tickets;
    tickets.open(argv[1]);
    // throw an error if we couldn't open the file
    if (!tickets)
    {
        cout << "Error: Could not open file for reading" << endl;
        return 0;
    }
    // loop until the end of the file
    while(!tickets.eof()){
        //put menu here
        	std::string dmenu = "======Main Menu=====\n"
					"1. Enqueue from file\n"
					"2. Enqueue from user\n"
                    "3. Dequeue\n"
                    "4. Remove selected passengers\n"
					"5. Remove all passengers\n"
					"6. Print train\n"
					"7. Print queue\n"
					
					"8. Quit";
    
    int choice;
    bool exit = false;
    
    cout << dmenu << endl;
    
    carPassengers *latest;
    while(cin >> choice) {
        
        // flush the newlines and other characters
        cin.clear();
        cin.ignore();

        switch (choice) {
            case 1:
            {
                if(latest != NULL && !myTrain.getQueue()->queueIsFull())
                {
                    bool success = myTrain.enqueuePassengers(*latest); //add item that couldn't be added before
                }
                //enqueue from file
                //For every line, separates destination and tickets, then adds passengers 
                string line;
                while(getline(tickets,line)) //Loops through every line
                {
                    cout << "y";
                    stringstream ss(line);
                    string partOfLine;
                    int i = 0;
                    carPassengers cp;
                    while(getline(ss, partOfLine, ','))//Separates destination and tickets
                    {
                        ss.ignore();
                        if(i == 0)
                        {
                            cp.carName = partOfLine;
                        }
                        else
                        {
                            cp.passengers = stoi(partOfLine);
                        }
                        i++;
                    }
                    cout << "x";//x
                    if(myTrain.getQueue()->queueIsFull())
                    {
                        *latest = cp; //keeps track of item that couldn't be added
                        std::cout << "yo";//x
                        break;
                    }
                    else
                    {
                        std::cout << cp.carName << "/" << cp.passengers << std::endl;//x
                        bool success = myTrain.enqueuePassengers(cp); //adds passengers
                    }
                }

                break;
            }
            
            case 2:
            {
				//enqueue from user
                string destination;
                int passengers;
                cout << "Where would you like to go?" << endl;
                cin >> destination;
                cout << "How many tickets would you like?" << endl;
                cin >> passengers;

                carPassengers cp;
                cp.carName = destination;
                cp.passengers = passengers;

                bool success = myTrain.enqueuePassengers(cp);
                break;
            }
            case 3:
            {
                //dequeue
                bool success = myTrain.dequeuePassengers();
                //passengers will be added to the train if success = true, that happens in dequeuePassengers
                break;
            }
            case 4:
            {
                //remove passengers
                //ask user for number of passengers and car
                string carName;
                int numPassengers;
                cout << "Enter name of car to remove from?" << endl;
                cin >> carName;
                cout << "Enter number of passengers to remove" << endl;
                cin >> numPassengers;

                myTrain.removePassengers(carName, numPassengers);
                break;
            }
            case 5:
            {
                //remove all passengers and delete cars
                trainCar *temp = myTrain.getEngine()->next;
                while(temp != myTrain.getCaboose())
                {
                    std::cout << "removed: " << temp->name << "\t" << temp->occupancy;
                    myTrain.removePassengers(temp->namePart(), temp->occupancy);
                }
                delete temp;
                break;
            }
            case 6:
            {
                myTrain.printTrain();//print train
                break;
            }
            case 7:
            {
                myTrain.getQueue()->printQueue();//print queue
                break;
            }
            case 8:
            {
                exit = true;
                break;
            }
        }
        
        if (exit) {
            delete latest;
            break;
        }
        
        cout << dmenu << endl;
    }

    

    }    

}