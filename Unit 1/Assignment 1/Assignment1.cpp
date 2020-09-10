/*
Florian Frick
Assignment 1
Hoenigman

The open lockers are all perfect squares because normal factor, cancel each other out where the first number opens the locker and the second number closes it again.
If a factor has the same number multiplied by itself, however, the locker isn't closed by the corresponding factor.
*/

#include <iostream>

using namespace std;

void locker()
{
        bool lockers[100] = {false}; //Array of boolean lockers (true=open)

    //for each pass through of every locker, it toggles every locker j whose modulous of i, the pass through number, is zero
    for(int i = 1; i <= 100; i++)
    {
        for(int j = 1; j <= 100; j++)
        {
            if(j % i == 0)
            {
                lockers[j-1] = !lockers[j-1];
            }
        }
    }

    //Counts how many lockers are open and prints out their indices
    std::cout << "Indices of Open Lockers: ";
    int numOpen = 0;
    for(int i = 1; i <= 100; i++)
    {
        if(lockers[i-1])
        {
            numOpen++;
            std::cout << i << ", ";
        }
    }

    std::cout << "\n Number of Lockers Open: " << numOpen << endl;
}

void circus()
{
    struct person
    {
        int height;
        int weight;
    };

    person one = {65,100};
    person two = {70, 150};
    person three = {56,90};
    person four = {75,190};
    person five = {60, 95};
    person six = {68,110};
    person people[6] = {one, two, three, four, five, six};
    
    //sorts people by height
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5-i; j++)
        {
            if(people[j].height > people[j+1].height)
            {
                person temp = {people[j]};
                people[j] = people[j+1];
                people[j+1] = temp;
            }
        }
    }

    int max = 6; //max tower size

    //sorts people by weight, if height contradicts weight, removes person from list by moving them to the end and reducing considered array size. Implementation wouldn't find maximum tower size in every case, currently
    for(int i = 0; i < max-1; i++)
    {
        for(int j = 0; j < max-1-i; j++)
        {
            if(people[j].weight > people[j+1].weight)
            {
                if(people[j].height < people[j+1].height) //removes person j by moving person to end of list and subtracting 1 from max tower size
                {
                    for(int k = j; k < max-1; k++)
                    {
                        person temp = {people[k]};
                        people[k] = people[k+1];
                        people[k+1] = temp;
                    }
                    
                    max--;
                }
                else
                {
                    person temp = {people[j]};
                    people[j] = people[j+1];
                    people[j+1] = temp;
                }
            }
        }
    }

    //prints order and max tower size
    for(int i = 0 ; i < max; i++)
    {
        std::cout << "(" << people[i].height << "," << people[i].weight << "), ";
    }
    cout << "Maximum Sized Tower: " << max;

}


int main()
{
    locker();
    circus();


    return 0;
}

