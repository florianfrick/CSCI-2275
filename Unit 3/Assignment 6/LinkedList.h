//
//  BST.h
//  Assignment-6    
//  CSCI 2275
//

#ifndef LL_H
#define LL_H

#include <string>


struct wordNode
{
    std::string word;
    int count;
    wordNode *next;
    wordNode *previous;

    wordNode();
    wordNode(std::string in_word, wordNode *n, wordNode *p, int c)
    {
        word = in_word;
        next = n;
        previous = p;
        count = c;
    };
};

class LinkedList
{
    private:
        wordNode *head;
    public:
        LinkedList();
        bool insertWord(std::string word);
        bool insertWordNode(wordNode *newNode);
        void printLL();
        int countNodes();
        int countTotalWords();
};

#endif // LL_H