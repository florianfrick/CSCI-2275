#include "BST.h"
#include <iostream>

BST::BST()
{
}
BST:: ~BST()
{
    DestroyRecursive(root);
}
void BST::DestroyRecursive(BSTNode *root)
{
    if(root)
    {
        DestroyRecursive(root->leftChild);
        DestroyRecursive(root->rightChild);
        delete root;
    }
}
void BST::printWord(std::string word)
{
    BSTNode *temp = root;

    if(root == NULL)
    {
        std::cout << "Error printing word: BST is Empty" << std::endl;
        return;
    }

    while(temp != NULL)
    {
        if(word == temp->word)
        {
            std::cout << "Word: " << word << std::endl;
            std::cout << "Count: " << temp->count << std::endl;
            if(temp->parent != NULL)
            {
                std::cout << "Parent: " << temp->parent->word << std::endl;
            }
            else
            {
                 std::cout << "Parent: no parent " << std::endl;
            }
            
            if(temp->leftChild != NULL)
            {
                std::cout << "Left Child: " << temp->leftChild->word << std::endl;
            }
            else
            {
                std::cout << "Left Child: no left child" << std::endl;

            }
            
            if(temp->rightChild != NULL)
            {
                std::cout << "Right Child: " << temp->rightChild->word << std::endl;
            }
            else
            {
                std::cout << "Right Child: no right child"  << std::endl;
            }
            
            break;
        }
        else if(word < temp->word)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }
}

void BST::printInOrderBST()
{
    if(root == NULL)
    {
       std::cout << "Error printing BST: BST is Empty" << std::endl;
    }
    else
    {
        return printBST(root);
    }    
    
}
int BST::countBSTNodes()
{
    if(root == NULL)
    {
        return 0;
    }
    int counter = 0;
    countBSTNodes(root, &counter);
    return counter;
}
int BST::countBSTTotalWords()
{
    if(root == NULL)
    {
        return 0;
    }
    int sum = 0;
    countBSTTotalWords(root, &sum);
    return sum;
}
int BST::addWordNode(std::string word)
{
    if(root == NULL)
    {
        //first item to be added to BST
        BSTNode *newNode = new BSTNode(word, NULL, NULL, NULL);
        root = newNode;
        return 1;
    }

    int numComparisons = 0;
    BSTNode *node = searchBST(word, numComparisons);
    if(node == NULL)
    {
        std::cout << "Error: bst search result: null" << std::endl;
        return 0;
    }
    if(node->word == word)
    {
        node->count = node->count + 1; //increment count
    }
    else
    {
        //node must be added
        BSTNode *newNode;
        if(word < node->word)
        {
            //new node is left child
            newNode = new BSTNode(word, node, NULL, NULL);

             node->leftChild = newNode;
        }
        else
        {
            //new node is right child
            newNode = new BSTNode(word, node, NULL, NULL);

            node->rightChild = newNode;
        }
    }    

    return numComparisons;
}
void BST::findAlphaRange(std::string word1, std::string word2) //print the words in the tree between word1 and word2
{
    int c1 = 0;
    int c2 = 0;
    BSTNode *node1 = searchBST(word1, c1);
    BSTNode *node2 = searchBST(word2, c2);

    if(node1->word != word1 || node2->word != word2)
    {
        std::cout << "One or more words does not exist in the tree" << std::endl;
    }
    else
    {
        if(word1 < word2)
        {
            printRange(root, word1, word2);//root, node1?
        }
        else
        {
            printRange(root, word2, word1);//root, node1?
        }
    }
}

void BST::printRange(BSTNode * node, std::string word1, std::string word2)
{
    if(node == NULL)
    {
        return;
    }

    printRange(node->leftChild, word1, word2);
    if(node->word > word1 && node->word < word2)
    {
        std::cout << node->word << std::endl;
    }
    printRange(node->rightChild, word1, word2);
}

void BST::printBST(BSTNode * node)
{
    if(node == NULL)
    {
        return;
    }

    printBST(node->leftChild);
    std::cout << node->count << " " << node->word << std::endl;
    printBST(node->rightChild);

}
void BST::printPreOrderBST(BSTNode * node)
{
    std::cout << node->word << std::endl;
    if(node->leftChild != NULL)
    {
        printBST(node->leftChild);
    }
    if(node->rightChild != NULL)
    {
        printBST(node->rightChild);
    }
}
void BST::countBSTNodes(BSTNode *node, int *c)
{
    if(node != NULL)
    {
        (*c) += 1; //increment counter
        countBSTNodes(node->leftChild, c);
        countBSTNodes(node->rightChild, c);
    }
    
}
void BST::countBSTTotalWords(BSTNode *node, int *s)
{
    if(node != NULL)
    {
        (*s) += node->count; //increment sum
        countBSTTotalWords(node->leftChild, s);
        countBSTTotalWords(node->rightChild, s);
    }
}
BSTNode* BST::searchBST(std::string word, int &opCounter) //use this function to find pointer to node in BST
{
    BSTNode *temp = root;

    while(temp != NULL)
    {
        opCounter = opCounter +1;//increment counter
        if(word == temp->word)
        {
            return temp; // word was in BST
        }
        else if(word < temp->word)
        {
            if(temp->leftChild == NULL)
            {
                return temp; //returns parent of where word would go
            }
            temp = temp->leftChild;
        }
        else
        {
            if(temp->rightChild == NULL)
            {
                return temp; //returns parent of where word would go
            }
            temp = temp->rightChild;
        }
    }
    return temp;
}
    