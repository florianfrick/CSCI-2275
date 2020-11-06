#include "LinkedList.h"
#include "BST.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool structureAdd(std::string filename, int numLines, BST *bst, LinkedList *ll)
{
    ifstream inStream; // stream for reading in file
    inStream.open(filename); // open the file

    // throw an error if we couldn't open the file
    if (!inStream)
    {
        cout << "Error: Could not open file for reading" << endl;
        return false;
    }

    int llComparisons = 0;
    int bstComparisons = 0;
    int wordCount = 0;
    // loop until the end of the file
    int i = 0;
    string line;
    while (getline(inStream, line) && i < numLines) // reads i lines
    {
        i++;
        stringstream ss(line); //stores line
        string word; //stores word
        while(ss >> word) // reads every word
        {
            wordCount++; //increments count
                                                            //cout << "word: " << word << endl; //debug purposes
            int llComps = ll->insertWord(word); // ll add
            int bstComps = bst->addWordNode(word); // bst add

            //Adds the number of comparisons used to add each word
            //cout << "LL comparison add: " << llComps << endl;
            //cout << "BST comparison add: " << bstComps << endl;

            llComparisons += llComps; //increments comparison number
            bstComparisons += bstComps; //increments comparison number
        }
    }

    inStream.close();// close the file
    
    //output data
    cout << "Number of Lines: " << numLines << endl;
    // cout << "Number of Words: " << wordCount << endl;
    cout << "\t LL Comparison Average: " << llComparisons/wordCount << endl;
    cout << "\t BST Comparison Average: " << bstComparisons/wordCount << endl;

    //cout << "\t LL Standard Deviation: " <<  << endl;
    //cout << "\t BST Standard Deviation: " <<  << endl;


    cout << "LL Unique Words: " << ll->countNodes() << endl;
    cout << "BST Unique Words: " << bst->countBSTNodes() << endl;

    cout << "LL Total Words: " << ll->countTotalWords() << endl;
    cout << "BST Total Words: " << bst->countBSTTotalWords() << endl;

    return true;
}

int main(int argc, char* argv[])
{
    // verify we have the correct number of parameters, else throw error msg & return
    if (argc < 2)
    {
        cout << "Usage: Assignment6Solution <inputfilename.txt>" << endl;
        return 0;
    }

        
    BST *bst = new BST();
    LinkedList *ll = new LinkedList();
    structureAdd(argv[1], 1800, bst, ll); //function that processes file and outputs data, second parameter determines number of line read


    string menu = "\n======Main Menu=====\n"
					"1. Print Word\n"
					"2. Print Tree In Order\n"
                    "3. Find Words in Range\n"
                    "4. quit\n";
    
    cout << menu << endl;
    int choice;
    bool exit = false;
    while(cin >> choice)
    {
        cin.clear();
        cin.ignore();
        switch (choice)
        {
                case 1:
                {
                    cout << "Word to print:" << endl;
                    string word;
                    cin >> word;
                    bst->printWord(word);
                    break;
                }
                case 2:
                {
                    bst->printInOrderBST();
                    break;
                }
                case 3:
                {
                    string word1, word2;
                    cout << "Word to find range between" << endl;
                    cin >> word1;
                    cin >> word2;
                    cout << endl;
                    bst->findAlphaRange(word1, word2); //prints words between the two words
                    break;
                }
                case 4:
                {
                    exit = true;
                    return 0;
                }
        }
        if (exit)
        {
                return 0;
        }
            
        cout << menu << endl;
    }
}
