#include "Queue.h"
#include "Stack.h" 
#include <string> 

int main() {

    string animals[10] = {"Dog", "Cat", "Leopard", "Raccoon", "Mountain Lion", "Owl", "Hawk"
                          "Red Panda", "Penguin", "Fennec Fox"};
    circQueue myQ(8);
    ArrStack myStack(10); 


    // Push 5 values from animals[] into the queue
    for(int i = 0; i < 5; i++)
    {
        myQ.enqueue(animals[i]);
    }

    // Using the Queue, pop out one value at a time
    // Push the popped values into an array Stack 
    // Repeat until the Queue is empty
    while(!myQ.isEmpty())
    {
        myStack.push(myQ.dequeue());
    }

    // Pop values from stack, printing them as you do
    while(!myStack.isEmpty())
    {
        cout << myStack.pop() << endl;
    }

    cout << endl << endl;

    // Repeat for the rest of the values in animals[]
    for(int i = 5; i < 10; i++)
    {
        myQ.enqueue(animals[i]);
    }

    while(!myQ.isEmpty())
    {
        myStack.push(myQ.dequeue());
    }

    while(!myStack.isEmpty())
    {
        cout << myStack.pop() << endl;
    }


    return 0;
}