#include <iostream>

using namespace std;

#define SEPARATOR "#<ab@17943918#@>#"

/* DO NOT MODIFY */
struct headNode;
struct DLLNode{
    int key;
    DLLNode *next;
    DLLNode *previous;
    headNode *head;
    DLLNode(DLLNode *n, DLLNode *p, headNode *hn, int k){
        next = n;
        previous = p;
        key = k;
        head = hn;
    }
};
struct SLLNode{
    int key;
    SLLNode *next;
    SLLNode(SLLNode *sll, int k){
        next = sll;
        key = k;
    }
};

struct headNode{
    SLLNode *nextSLL = nullptr;
    DLLNode *nextDLL = nullptr;
    string name;
    headNode(SLLNode *sll, DLLNode *dll, string n){
        nextSLL = sll;
        nextDLL = dll;
        name = n;
    }
};


/* DO NOT MODIFY */
class LinkedList{
   private:
      headNode *hn;
      //Node *search(int val);
   public:
      LinkedList(){
         hn = new headNode(nullptr, nullptr, "head node");
      };
      void insertSLLNode(int leftVal, int newVal);
      void insertDLLNode(int leftVal, int newVal);
      SLLNode* searchSLL(int val);
      DLLNode* searchDLL(int val);

      void printSLLList();
      void printDLLList();
      void findMinAndAddAfter(int val);
};

/* DO NOT MODIFY */
void LinkedList::insertSLLNode(int leftValue, int value) {
   SLLNode* left = searchSLL(leftValue);
   SLLNode* node = new SLLNode(nullptr, value);
   
   if (left == nullptr) { /* inserting a new head node */
      if(hn->nextSLL == nullptr){
         hn->nextSLL = node;
      }else{
         node->next = hn->nextSLL;
         hn->nextSLL = node;
      }
   }
   else if (left->next == nullptr) { /* inserting a new tail node */
      left->next = node;
      if (hn->nextSLL == nullptr) 
         hn->nextSLL = node;
   }
   else { /* inserting a node in the middle */
      node->next = left->next;
      left->next = node;
   }
}

/* DO NOT MODIFY */
void LinkedList::insertDLLNode(int leftVal, int value) {
   DLLNode* left = searchDLL(leftVal);
   DLLNode* node = new DLLNode(nullptr, left, nullptr, value);
   
   if (left == nullptr) { /* inserting a new head node */
      if(hn->nextDLL == nullptr){
         hn->nextDLL = node;         
      }else{
         node->next = hn->nextDLL;
         hn->nextDLL = node;
      }
   }else if (left->next == nullptr) { /* inserting a new tail node */
      left->next = node;
      node->previous = left;
      if (hn->nextDLL == nullptr) {
         hn->nextDLL = node;
         node->head = hn;
      }
   }
   else { /* inserting a node in the middle */
      node->next = left->next;
      left->next->previous = node;
      left->next = node;
      node->previous = left;
   }
}

/* DO NOT MODIFY */
SLLNode* LinkedList::searchSLL(int val) {
   SLLNode* current = hn->nextSLL;
   while (current != nullptr) {
      if (current->key == val)
         return current;
      current = current->next;
   }
   return nullptr;
}

/* DO NOT MODIFY */
DLLNode* LinkedList::searchDLL(int val) {
   DLLNode* current = hn->nextDLL;
   while (current != nullptr) {
      if (current->key == val)
         return current;
      current = current->next;
   }
   return nullptr;
}

/* DO NOT MODIFY */
void LinkedList::printSLLList()
{
   SLLNode *current = hn->nextSLL;
   
   while (current != nullptr)
   {
      cout << current->key << " ";
      current = current->next;
   }
}
/* DO NOT MODIFY */
void LinkedList::printDLLList()
{
   DLLNode *current = hn->nextDLL;
   
   while (current != nullptr)
   {
      cout << current->key << " ";
      current = current->next;
   }
}

void LinkedList::findMinAndAddAfter(int value){
   SLLNode *tempSLL = hn->nextSLL;
   DLLNode *tempDLL = hn->nextDLL;

   SLLNode *minSLL = hn->nextSLL;
   DLLNode *minDLL = hn->nextDLL;
   //find min value in SLL
   int minSLLVal;
   while(tempSLL != NULL)
   {
      if(tempSLL->key < minSLLVal)
      {
         minSLLVal = tempSLL->key;
         minSLL = tempSLL;
      }
      tempSLL = tempSLL->next;
   }
   //find min value in DLL
   int minDLLVal;
   while(tempDLL != NULL)
   {
      if(tempDLL->key < minDLLVal)
      {
         minDLLVal = tempDLL->key;
         minDLL = tempDLL;
      }
      tempDLL = tempDLL->next;
   }

   //determine if min value is in SLL or DLL
   if(minSLLVal < minDLLVal)
   {
      insertSLLNode(minSLLVal, value);
   }
   else if(minDLLVal < minSLLVal)
   {
      insertDLLNode(minDLLVal, value);
   }
   else
   {
      insertSLLNode(minSLLVal, value);
      insertDLLNode(minDLLVal, value);
   }
}

int main()
{
   LinkedList *ll = new LinkedList();
   //Test cases
   //Test case 1
   //SLL = 1-2-3-4, and DLL = 10-20-30-40, add node with 5
   //output 1-5-2-3-4 for SLL, DLL unchanged

   //Test case 2
   //DLL = 1-2-3-4, and SLL = 10-20-30-40, add node with 5
   //output 1-5-2-3-4 for DLL, DLL unchanged

   //Test case 3
   //SLL = 4-3-2-15, and DLL = 5-6-3-20, add node with 10
   //output 4-3-2-10-15 for SLL, and DLL unchanged

   //Test case 4
   //DLL = 4-3-2-15, and SLL = 5-6-3-20, add node with 10
   //output 4-3-2-10-15 for DLL, and SLL unchanged

   //Test case 5
   //SLL = 4-3-2-1, and DLL = 12-13-14-15, add node with 20
   //output 4-3-2-1-20 for SLL, and DLL unchanged
   
   //Example of how to build test cases.
   //Test case code to build the SLL and DLL
   //Test case #1
   for(int i=1;i < 5;i++){
      ll->insertSLLNode(i-1,i);
   }
   ll->printSLLList();
   
   for(int i=10; i < 50; i+=10){
      ll->insertDLLNode(i-10,i);
   }
   ll->printDLLList();

   cout << endl;

/*
   //Test case 3
   ll->insertSLLNode(0, 4);
   ll->insertSLLNode(4, 3);
   ll->insertSLLNode(3, 2);
   ll->insertSLLNode(2, 15);

   ll->insertDLLNode(0, 5);
   ll->insertDLLNode(5, 6);
   ll->insertDLLNode(6, 3);
   ll->insertDLLNode(3, 20);
   
   ll->printSLLList();
   ll->printDLLList(); 
 
   */

   return 0;
}