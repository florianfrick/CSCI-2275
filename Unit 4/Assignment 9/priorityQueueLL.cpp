#include "priorityQueueLL.h"
#include <iostream>

priorityQueueLL::priorityQueueLL()
{
    head = NULL;
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
bool priorityQueueLL::insertWord(std::string name, int priority, int treatment) 
{
    /*add word to words array in priority order. Returns true if word added
    Creates new LLNodes for comparisons
    Deletes these LLNodes to unallocate memory*/
    if(head == NULL)
    {
        //first item
        LLNode *newNode = new LLNode(name, priority, treatment, NULL, NULL);
        insertLLNode(NULL, newNode);
        return true;
    }

    LLNode *newNode = new LLNode(name, priority, treatment, head, NULL);
    if(LLNode::oneIsSmallerPriority(newNode, head))
    {
        //should be added before head by priority
        insertLLNode(NULL, newNode);
        return true;
    }
    delete newNode;
    LLNode *temp = head;
    while(temp->next != NULL)
    {
        newNode = new LLNode(name, priority, treatment, temp, temp->previous);
        if(LLNode::oneIsSmallerPriority(newNode, temp))
        {
            //new object's priority is smaller, and therefore more important than, temp's
            insertLLNode(temp->previous, newNode);
            return true;
        }
        temp = temp->next;
        delete newNode;

        //add item to end of the list if necessary
        if(temp->next == NULL)
        {
            LLNode *newNode = new LLNode(name, priority, treatment, NULL, temp);
            insertLLNode(temp, newNode);
            return true;
        }
    }
    return false;
}

LLNode* priorityQueueLL::pop()
{
    if(head == NULL)
    {
        return NULL;
    }
    LLNode *removed = head;
    head = head->next;
    if(head != NULL)
    {
        head->previous = NULL;
    }
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
