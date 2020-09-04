#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct car
{
    string make;
    string model;
    string year;
};


int main(int argc, char *argv[])
{
    car cars[10] = {};

    ifstream inFile;
    string data;
    inFile.open(argv[1]); //open the file

    if (inFile.is_open())//error check
    {  
   	    cout << "Opened successfully" << endl;
        
        //adds information to array of struct car
        int i = 0;
   	    while (getline(inFile, data))
        {                      	 
   		    //cout << data << endl;

   		    stringstream ss(data);

            string make, model, year;
            ss >> make;
   		    ss >> model;
            ss >> year;

            car temp;
            temp.make = make;
            temp.model = model;
            temp.year = year;

            cars[i] = temp;
   		    i++;
   	     }
        
   	    inFile.close(); //close the file
    }   
    else
    {   
   	    cout << "File unsuccessfully opened" << endl;
    }

    //prints array to terminal
    for(car c: cars)
    {
        cout << c.make << "\t" << c.model << "\t" << c.year << endl;
    }


    return 0;
}