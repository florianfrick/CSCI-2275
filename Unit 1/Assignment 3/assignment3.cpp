// ==========================================
// Filename: Assignment3.cpp
// Author: Florian Frick
// Date: 9/25/2020
// Description: Counts unique words in a file
// outputs the top N most common words
// Uses TextAnalyzer class
// ==========================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "TextAnalyzer.h"
#include <string>
using namespace std;

// main expects 2 arguments, filename and number of top words
int main(int argc, char* argv[])
{
    //Dynamic Memory Excercises
    wordItem* wordsE = new wordItem[10];
    for(int i = 0; i < 10; i++)
    {
        wordsE[i].word = "default";
        wordsE[i].count = i*i;
        cout << "word: " << wordsE[i].word;
        cout << ", count: " << wordsE[i].count << endl;
    }

    int newI;
    cout << "At what index would you like to insert a new wordItem?" << endl;
    cin >> newI;
    if(newI < 10 && newI >= 0)
    {
        //shifts array to the right, starting at the end
        for(int i = 9; i > newI; i--)
        {
            wordsE[i].word = wordsE[i-1].word;
            wordsE[i].count = wordsE[i-1].count;
        }
        wordsE[newI].word = "test";
        wordsE[newI].count = 99;
    }
    for(int i = 0; i < 10; i++)
    {
        cout << "word: " << wordsE[i].word;
        cout << ", count: " << wordsE[i].count << endl;
    }

    cout << "At what index would you like to insert another new wordItem?" << endl;
    cin >> newI;
    wordItem* words2 = new wordItem[20];
    bool added = false;
    for(int i = 0, j = 0; i < 10; i++, j++)
    {
        if(i == newI)//new item
        {
            words2[j].word = "test2";
            words2[j].count = 100;
            i--;
            newI = -2;
            added = true;
        }
        else//old item copied
        {
            words2[j].word = wordsE[i].word;
            words2[j].count = wordsE[i].count;
        }
        cout << "word: " << words2[j].word;
        cout << ", count: " << words2[j].count << endl;
    }
    if(!added)
    {
        words2[newI].word = "test2";
        words2[newI].count = 100;
        cout << "word: " << words2[newI].word;
        cout << ", count: " << words2[newI].count << endl;
    }
    cout << endl << endl;
    delete[] wordsE;
    wordsE = words2;
    



    ifstream inStream;      // stream for reading in file
    bool commonWord;                  // flag for whether word is common word

    // verify we have the correct number of parameters, else throw error msg & return
    if (argc != 4)
    {
        cout << "Usage: Assignment3Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return 0;
    }

    int numCommon = atoi(argv[1]);
    TextAnalyzer *ta = new TextAnalyzer(argv[3], numCommon);
    // open the file
    inStream.open(argv[2]);


    // throw an error if we couldn't open the file
    if (!inStream)
    {
        cout << "Error: Could not open file for reading" << endl;
        return 0;
    }

    // loop until the end of the file
    while (!inStream.eof())
    {
        string word;
        bool wordFound;
        // read in a word
        inStream >> word;
        wordFound = ta->insertWord(word); //the insertWord method will call isIgnoreWord
        if(wordFound){
            //cout<<"word added: "<< word << endl;
        }else{
            //cout << word << " is a common word"<<endl;
        }
    }
        

    // close the file
    inStream.close();

    // sort the array by word count, should be currently in alpha order
    //ta->sortByWordCount();
 
    // print out the top N most common words in the document
    ta->printTopN(numCommon);
    // print how many time the array doubled
    cout << "#" << endl;
    cout << "Array doubled: " << ta->getNumDoublings() << endl;
    // print the unique non-common words
    cout << "#" << endl;
    cout << "Unique non-common words: "<< ta->getNumberOfUniqueWords() <<endl;
  
    // print out the total number of non-common words
    cout << "#" << endl;
    cout << "Total non-common words: " << ta->getTotalNonCommonWords() << endl;

    return 0;
}

