#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// struct to store word+count combinations
struct wordItem
{
    string word;
    int count;    
};

class TextAnalyzer{
    private:
        wordItem *words;
        wordItem *ignoreWords;
        int numIgnoreWords = 50;
        int numCommon = 0; //number of n to print
        int numDoublings = 0; // stores the times we double the array
        int numUniqueWords = 0;// stores the total number of unique words in the document, not counting stop words
        int arrLoc = 0;         // stores the location of the last element in the arr
        int arrCapacity = 100;   // stores the initial capacity of the array

        void buildStopWordsArray(std::string ignoreWordsFileName) //read file and populate stopWords array
        {
            ifstream file;
            file.open(ignoreWordsFileName);
            string line;
            ignoreWords = new wordItem [numIgnoreWords];
            int i = 0;
            while(getline(file, line))
            {
                if(i >= numIgnoreWords-1)
                {
                    ignoreWords[i].word = line;
                }
                else
                {
                    ignoreWords[i].word = line.substr(0, line.length()-1);
                }
                
                //cout << "substr: " << line;
                ignoreWords[i].count = 0;

                i++;
                     
            }
        }

        bool isIgnoreWord(std::string word)//read stopWords array and return true if word is in array, false otherwise
        {
            for(int i = 0; i < numIgnoreWords; i++)
            {                
                if(word == ignoreWords[i].word)
                {
                    return true; 
                }
            }
            return false;
        }

        void insertAt(std::string word, int index) //call in the insert method to add a word at specified index and shift rest of array
        {
            if(arrLoc+1 > arrCapacity-1)//array capacity must be greater than the index of last element
            {
                numDoublings += 1;
                arrCapacity *= 2;
                wordItem *temp = new wordItem[arrCapacity];
                for(int i = 0, j = 0; i < arrLoc+1; i++, j++)
                {
                    if(i == index)//adds new word
                    {
                        temp[j].word = word;
                        temp[j].count = 1;
                        j++;
                    }
                        temp[j].word = words[i].word;
                        temp[j].count = words[i].count;
                }

                delete[] words;
                words = temp;
            }
            else
            {
                for(int i = arrLoc; i > index; i--)
                {
                    words[i].word = words[i-1].word;
                    words[i].count = words[i-1].count;
                }
                words[index].word = word;
                words[index].count = 1;
            }            
        }

        

    public:
        TextAnalyzer(){}; 
        //in constructor, allocate memory for ignoreWords and words arrays and populate ignoreWords
        TextAnalyzer(std::string ignoreWordsFile, int numCommon)
        {
            this->numCommon = numCommon;
            words = new wordItem[100];
            buildStopWordsArray(ignoreWordsFile);
        }

        bool insertWord(std::string word) //add word to words array in alphabetical order. Returns true if word inserted or count increased and false if the word is a stop word
        {
            if(isIgnoreWord(word))//checks if word is common
            {
                return false;
            }
            
            int i;
            for(i = arrLoc; i >= 0 &&  (words[i].word >= word || words[i].word == ""); i--)//determine where to add word, or if it already is in the list
            {
                if(words[i].word == word)//word is in list
                {
                    words[i].count = words[i].count + 1; //increment count
                    return true;
                }

            }
            insertAt(word, i+1);
            arrLoc += 1;
            numUniqueWords += 1;
            return true;
        }
        
        void sortByWordCount() //not used
        {
            for(int i = 0; i < arrLoc-1; i++)
            {
                for(int j = 0; j < arrLoc-i-1; j++)
                {
                    if(words[j].word > words[j+1].word)
                    {
                        swap(words[j], words[j+1]);
                    }
                }
            }
        }


        void printTopN(int topN)
        {
            wordItem *tops = new wordItem[topN];
            for(int i = 0; i < topN; i++)
            {
                tops[i] = words[i];
            }

            for(int i = 0; i < arrLoc; i++)
            {
                if(words[i].count > tops[topN-1].count) //count is in the topN
                {
                    tops[topN-1] = words[i];
                    for(int j = topN-1; j > 0; j--) //determines topN position
                    {
                        if(tops[j].count > tops[j-1].count)
                        {
                            swap(tops[j-1], tops[j]);
                        }
                    }
                }
            }

            for(int i = 0; i < topN; i++)
            {
                cout << tops[i].count;
                cout << " - ";
                cout << tops[i].word;
                cout << endl;
            }
        }

        int getNumberOfUniqueWords()
        {
            return numUniqueWords;
        }

        int getNumDoublings()
        {
            return numDoublings;
        }

        int getTotalNonCommonWords() //output the sum of counts for each non-common word
        {
            int sum = 0;
            for(int i = 0; i < arrLoc; i++)
            {
                sum += words[i].count;
            }
            return sum;
        }
};