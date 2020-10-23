//
//  BST.h
//  Assignment-6    
//  CSCI 2275
//

#ifndef BST_H
#define BST_H

#include <string>

struct BSTNode{
    std::string word;
    int count;
    BSTNode* parent;
    BSTNode* leftChild;
    BSTNode* rightChild;
    
    BSTNode(std::string in_word, BSTNode *p, BSTNode *lc, BSTNode *rc)
    {
        word = in_word;
        count = 0;
        parent = p;
        leftChild = lc;
        rightChild = rc;
    };
};


class BST
{
    
public:
    BST();
    void printWord(std::string word);
    void printInOrderBST();
    int countBSTNodes();
    int addWordNode(std::string word);
    void findAlphaRange(std::string word1, std::string word2); //print the words in the tree between word1 and word2
    
protected:
    
private:
    void printBST(BSTNode * node);
    void printPreOrderBST(BSTNode * node);
    void countBSTNodes(BSTNode *node, int *c);
    BSTNode* searchBST(std::string word, int &opCounter); //use this function to find pointer to node in BST
        
    BSTNode* root;
};

#endif // BST_H
