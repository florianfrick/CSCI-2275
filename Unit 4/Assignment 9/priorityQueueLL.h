#ifndef LL_H
#define LL_H

#include <string>

struct LLNode
{
    std::string name;
    int priority;
    int treatment;
    LLNode *next;
    LLNode *previous;

    //constructor
    LLNode(std::string n, int p, int t, LLNode *nex, LLNode *prev)
    {
        name = n;
        priority = p;
        treatment = t;
        next = nex;
        previous = prev;
    }

    //comparison method for two nodes using priority and treatment
    static bool oneIsSmallerPriority(LLNode *one, LLNode *two)
    {
        if(one->priority < two->priority)
        {
            return true;
        }
        else if(one->priority == two->priority)
        {
            if(one->treatment < two->treatment)
            {
                return true;
            }
            return false;
        }
        else
        {
            return false;
        }
    }
};

class priorityQueueLL
{
    private:
        bool insertLLNode(LLNode *previous, LLNode *newNode);
    public:
        priorityQueueLL();
        ~priorityQueueLL();
        bool insertWord(std::string name, int priority, int treatment);
        LLNode* pop();
        void printLL();
        int countNodes();
        int countTotalWords();
        LLNode *head;
};

#endif // LL_H