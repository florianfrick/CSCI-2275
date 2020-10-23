#include "LinkedList.h"

LinkedList::LinkedList()
{
    head = NULL;
}
bool insertWord(std::string word) //add word to words array in alphabetical order. Returns true if word inserted or count increased and false if the word is a stop word
{
    wordNode *temp = head;
    bool found = false;
    while(temp != NULL && !found)
    {
        if(temp->word < word && temp->word != "")//found where word should be added
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
        }
        temp = temp->next;
    }
        return true;
}
bool insertWordNode(wordNode *previous, wordNode *newNode)
{
     /*1. check if the given prev_node is NULL */
    if (previous == NULL) { 
        head = newNode;
        return true;
    } 
    
    newNode->next = previous->next;
    previous->next = newNode;
    newNode->previous = previous;
  
    if (newNode->next != NULL)
    {
        newNode->next->previous = newNode; 
    }
    return true;
}
void LinkedList::printLL()
{

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
        sum = temp->count;
        temp = temp->next;
    }
    return sum;
}