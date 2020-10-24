#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList()
{
}
LinkedList::~LinkedList()
{
    wordNode* current = head;
    wordNode* next;

    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
}
int LinkedList::insertWord(std::string word) //add word to words array in alphabetical order. Returns true if word inserted or count increased
{
    if(head == NULL)
    {
        wordNode *newNode = new wordNode(word, NULL, NULL, 1);
        insertWordNode(NULL, newNode);
        return 1;
    }
    
    if(word < head->word)
    {

        wordNode *newNode = new wordNode(word, head, NULL, 1);
        insertWordNode(NULL, newNode);
        return 1;
    }

    int counter = 0;
    wordNode *temp = head;
    bool found = false;
    while(temp != NULL && !found)
    {
        counter++;
        if(temp->word >= word)//found where word should be added
        {
            found = true;
            if(temp->word == word)
            {
                //word is in list
                temp->count = temp->count + 1; //increment count
            }
            else
            {
                //word is not in the list, add node
                wordNode *newNode = new wordNode(word, temp, temp->previous, 1);
                insertWordNode(temp->previous, newNode);
            }
            return counter;
        }

        //add item to end of the list if necessary
        if(temp->next == NULL && !found)
        {
            wordNode *newNode = new wordNode(word, NULL, temp, 1);
            insertWordNode(temp, newNode);
            return counter;
        }

        temp = temp->next;
    }
    return counter;
}
bool LinkedList::insertWordNode(wordNode *previous, wordNode *newNode)
{
    if(previous == NULL)
    {
        if(head == NULL)
        {
            head = newNode; //first node
        }
        else
        {
            head->previous = newNode;
            head = newNode;
        }
        
        return true;
    }
    
    previous->next = newNode;
  
    if (newNode->next != NULL)
    {
        newNode->next->previous = newNode; 
    }
    return true;
}
void LinkedList::printLL()
{
    wordNode *temp = head;
    while(temp!= NULL)
    {
        std::cout << temp->count << " " << temp->word << std::endl;
        temp = temp->next;
    }
}
int LinkedList::countNodes()
{
    int counter = 0;
    wordNode *temp = head;
    while(temp != NULL)
    {
        counter ++;
        temp = temp->next;
    }
    return counter;
}
int LinkedList::countTotalWords()
{
    int sum = 0;
    wordNode *temp = head;
    while(temp != NULL)
    {
        sum += temp->count;
        temp = temp->next;
    }
    return sum;
}