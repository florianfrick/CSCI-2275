#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



int main(int argc, char* argv[])
{
    ifstream file;
    file.open(argv[1]);

    int size = 10;
    int* arr = new int[size];
    

    string line;
    int i = 0;
    while(getline(file,line))
    {
        if(i >= size-1)
        {
            size *= 2;
            int* arr2 = new int[size];
            for(int j = 0; j < size/2; j++)
            {
                arr2[j] = arr[j];
            }
            delete[] arr;
            arr = arr2;
        }
        arr[i] = stoi(line);
        i++;
    }
    file.close();

    for(int i = 0; i < size; i++)
    {
        cout << arr[i] << ", ";
    }

}

