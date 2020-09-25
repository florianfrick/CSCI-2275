#include<iostream>
#include<vector>

using namespace std;
class Elevator{
    private:
        int topFloor=10;
        int currentFloor=1;
        int bottomFloor=0;
    public:
        Elevator(){}
        int getCurrentFloor(){
            return currentFloor;
        }
        void setCurrentFloor(int cf){
            currentFloor = cf;
        }

    public:
        void goUpOneFloor()
        {
            if(currentFloor == topFloor)
            {
                cout << "Already at the top" << endl;
            }
            else
            {
                currentFloor += 1;
                cout << "Now at floor "<< currentFloor << endl;
            }
        }

    public:
        void goDownOneFloor()
        {
            if(currentFloor == bottomFloor)
            {
                cout << "Already at the bottom" << endl;
            }
            else
            {
                currentFloor -= 1;
                cout << "Now at floor "<< currentFloor << endl;
            }
        }

    public:
        Elevator(int top, int bottom, int current)
        {
            topFloor = top;
            bottomFloor = bottom;
            currentFloor = current;
        }

    public:
        void elevatorDescription()
        {
            cout << "top floor=" << topFloor << "\nbottom floor=" << topFloor << "\ncurrent floor=" << topFloor << endl;
        }
};

int main(int argc, char* argv[]){
    Elevator ev;
    cout<<ev.getCurrentFloor()<<endl;
    
    vector<Elevator> elevators;
    for(int i = 0; i < atoi(argv[1]); i++)
    {
        Elevator newElevator(10,0,0);
        elevators.push_back(newElevator);
    }

    int elevatorIndex;
    int destination;

    cout << "What elevator would you like to call?" << endl;
    cin >> elevatorIndex;
    if(elevatorIndex >= elevators.size() || elevatorIndex < 0)
    {
        cout << "No such elevator exists." << endl;
    }
    else
    {
        cout << "To what floor do you want to go?" << endl;
        cin >> destination;

    
        int currentLoc = elevators.at(elevatorIndex).getCurrentFloor();

        for(int i = 0; i < abs(destination - currentLoc); i++)
        {
            if(destination > elevators.at(elevatorIndex).getCurrentFloor())
            {
                elevators.at(elevatorIndex).goUpOneFloor();
            }
            else
            {
                elevators.at(elevatorIndex).goDownOneFloor();
            }
        
        }
        
    }
}