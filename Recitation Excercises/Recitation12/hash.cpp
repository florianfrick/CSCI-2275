// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
    this->tableSize= bsize;
    table = new node*[tableSize];
    for(int i=0;i<bsize;i++)
        table[i] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % tableSize);
}

// TODO Complete this function
//function to search
//Compute the index by using the hash function
node* HashTable::searchItem(int key)
{

    node* temp = table[hashFunction(key)];
    while(temp)
    {
        if(temp->key == key)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

//TODO Complete this function
//function to insert
// TODO :
// Use the hash function on the key to get the index/slot,
// create a new node with the key and insert it in this slot's list
bool HashTable::insertItem(int key)
{
    node* newNode = new node;
    newNode->key = key;
    int i = hashFunction(key);
    node* temp = table[i];
    if(temp == NULL)
    {
        table[i] = newNode;
        return true;
    }
    while(temp->next != NULL)
    {
        if(temp->key == key)
        {
            std::cout << "Duplicate: " << key << std::endl;
            return false;
        }
        temp = temp->next;
    }
    temp->next = newNode;
    return true;
}

//TODO Complete this function
// function to display hash table
void HashTable::printTable()
{
    for(int i = 0; i < tableSize; i++)
    {
        std::cout << "\n" << i << " || ";
        node* temp = table[i];
        while(temp)
        {
            std::cout << temp->key << " ";
            temp = temp->next;
        }
    }
}