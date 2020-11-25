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

    LLNode(std::string n, int p, int t, LLNode *nex, LLNode *prev)
    {
        name = n;
        priority = p;
        treatment = t;
        next = nex;
        previous = prev;
    }
};

class priorityQueueLL
{
    private:
        bool insertLLNode(LLNode *previous, LLNode *newNode);
    public:
        priorityQueueLL();
        ~priorityQueueLL();
        bool insertWord(LLNode *obj);
        LLNode* pop();
        void printLL();
        int countNodes();
        int countTotalWords();
        LLNode *head;
};

#endif // LL_H