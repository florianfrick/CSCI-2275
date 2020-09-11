/*
Florian Frick
Assignment 2
Hoenigman
*/


#include<sstream>
#include"MessageBoard.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //add to base code for students
#include <algorithm> //min

using namespace std;

// Function to read in the file and populate the items array, return the number of items in the array
void MessageBoard::readFile(string filename)
{
    //TO DO
	// Cycle through each line of the file
    //create an item and call checkForMatch for each line as it is read from file
    ifstream file;
    file.open(filename);
    string line;

    while(getline(file, line))
    {
        int sale;
        string type;
        int price;

        size_t lineProgress = 0;
        size_t commaLocation = line.find(',', lineProgress);
        
        type = line.substr(lineProgress, commaLocation);
        lineProgress += commaLocation + 1;
        commaLocation = line.find(',', lineProgress);

        string temp = line.substr(lineProgress, commaLocation-lineProgress);
        if(temp == ("for sale"))
        {
            sale = -1;
        }
        else
        {
            sale = 1;
        }

        lineProgress = commaLocation + 1;

        string t = line.substr(lineProgress);
        price = stoi(t);


        //item newItem{sale,type,price};
        item newItem;
        newItem.for_sale = sale;
        newItem.type = type;
        newItem.price = price;

       // cout << newItem.type << " " << newItem.for_sale << " " << newItem.price << endl;

        checkForMatch(newItem);
    }
}

void MessageBoard::checkForMatch(item newItem){
    //TO DO
    //determines if item passed in matches any item already in the items vector
    //if so, remove match from vector.
    //if no match is found, add item to the end of the vector

    vector<item>::iterator it;
    
    bool sold = false;
    for(it = items.begin(); !sold && it < items.end(); it++)//stops when item is sold
    {
        //verifies only one item is for sale, both items are of the same type, and the buyer can afford the item
        if(newItem.for_sale != it->for_sale && newItem.type == it->type && ( (newItem.for_sale < 0 && it->price >= newItem.price) || (newItem.for_sale > 0 && newItem.price >= it->price) ) )//for_sale must be -1 if newItem is for sale
        {
            //item sold
            sold = true;
            
            newItem.price = min(newItem.price, it->price);//makes the price of newItem into the price the item was sold at 
            items.erase(it); //deletes match
            
            printItemsSold(newItem);

        }
    }

    //add item to vector if it wasn't sold
    if(!sold)
    {
        items.push_back(newItem);
        //cout << newItem.for_sale << endl;//
    }
}

void MessageBoard::printItemsSold(item it){
    //TO DO
    //print type and price of item matched
    cout <<it.type<<" "<<it.price<<endl;


}
void MessageBoard::printItemsRemaining(){
    //TO DO
    //print all contents in items vector

    vector<item>::iterator it;
    
    for(it = items.begin(); it < items.end(); it++)//stops when item is sold
    {
        if(it->for_sale < 0)//
        {
            cout<<it->type<<", "<<"for sale"<<", "<<it->price<<endl;
        }
        else
        {
            cout<<it->type<<", "<<"wanted"<<", "<<it->price<<endl;
        }
    }
}
void MessageBoard::postItemToMessageBoard(string itemType, int price, int forSale){
    //TO DO
    //create an item and pass it to checkForMatch to determine if there is a match  

    item newItem;
    newItem.for_sale = forSale;
    newItem.type = itemType;
    newItem.price = price;

    //item newItem{forSale,itemType,price};

    checkForMatch(newItem);
}


