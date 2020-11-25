#include "priorityQueueLL.h"
#include <iostream>

priorityQueueLL::priorityQueueLL()
{
}
priorityQueueLL::~priorityQueueLL()
{
    LLNode* current = head;
    LLNode* next;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
}
bool priorityQueueLL::insertWord(LLNode *obj) //add word to words array in priority order. Returns true if word added
{
    if(head == NULL)
    {
        //first item
        insertLLNode(NULL, obj);
        return true;
    }
    
    if(obj->priority < head->priority)
    {
        //should be added before head by priority
        obj->next = head;
        insertLLNode(NULL, obj);
        return true;
    }
    else if(obj->priority == head->priority && obj->treatment <= head->treatment)
    {
        //should be added before head by treatment
        obj->next = head;
        insertLLNode(NULL, obj);
        return true;
    }

    LLNode *temp = head;
    bool found = false;
    while(temp != NULL && !found)
    {
        if(temp->priority >= obj->priority)
        {
            //found where word should be added
            found = true;
            obj->next = temp;
            obj->previous = temp->previous;
            insertLLNode(temp->previous, obj);
            return true;
        }

        //add item to end of the list if necessary
        if(temp->next == NULL && !found)
        {
            obj->previous = temp;
            insertLLNode(temp, obj);
            return true;
        }

        temp = temp->next;
    }
    return false;
}

LLNode* priorityQueueLL::pop()
{
    LLNode *removed = head;
    head->next->previous = NULL;
    head = head->next;
    return removed;
}

bool priorityQueueLL::insertLLNode(LLNode *previous, LLNode *newNode)
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
void priorityQueueLL::printLL()
{
    LLNode *temp = head;
    while(temp!= NULL)
    {
        std::cout << temp->name << " " << temp->priority << " " << temp->treatment << std::endl;
        temp = temp->next;
    }
}
int priorityQueueLL::countNodes()
{
    int counter = 0;
    LLNode *temp = head;
    while(temp != NULL)
    {
        counter ++;
        temp = temp->next;
    }
    return counter;
}
