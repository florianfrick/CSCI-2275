#include "Graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

// Graph::Graph()
// {
// }
// Graph::~Graph()
// {
//     //dtor
// }
void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    /*
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
                    */
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            std::cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.infected = false;
        v.groupID = 0;
        v.visited = false;
        vertices.push_back(v);

    }
}
void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++)
    {
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++)
        {
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}

//Outputs the ID group of everyone
void Graph::displayIDs()
{
    std::cout << "\nID Status:" << std::endl;
    for(vertex v: vertices)
    {
        std::cout << v.name << " " << v.groupID << std::endl;
    }
    std::cout << std::endl;
}

//Outputs the infection status of everyone
void Graph::displayInfections()
{
    std::cout << "\nInfection Status:" << std::endl;
    for(vertex v: vertices)
    {
        std::cout << v.name << (v.infected ? "\tinfected.":"\tnot infected.") << std::endl;        
    }
    std::cout << std::endl;
}

//This method is not used
int Graph::isAdjacent(std::string v1, std::string v2)
{
    vertex *root = findVertex(v1);

    //adds root to stack
    stack<string> stack;
    stack.push(v1);

    while(!stack.empty())
    {
        string v1 = stack.top();
        stack.pop();

        vertex *v = findVertex(v1);
        if(v->visited == false)
        {
            //determines if current vector has the desired string
            if(v->name == v2)
            {
                unvisit();
                std::cout << "Path found" << std::endl;
                return true;
            }
            v->visited = true;
        }

        //adds neighbors to stack
        for(adjVertex edge: v->adj)
        {
            if(edge.v->visited == false)
            {
                stack.push(edge.v->name);
            }
        }
    }

    unvisit();
    std::cout << "Path not found" << std::endl;
    return false;
}

//Assigns incrementing groupIDs to all connected individuals by using a Depth First Search algorithm
void Graph::assignGroupID()
{
    unvisit();
    int ID = 1;
    while(allVisited() == false)
    {
        for(vertex v : vertices)
        {
            //finds first vertex not assigned to a group, labels all connected vertices, and breaks out of the for loop
            if(v.groupID < 1)
            {
                DFSLabel(v.name,ID);
                break;
            }
        }
        ID++;
    }
    unvisit();
    displayIDs();
}

//Randomly infects one person and outputs their contacts with more than 15 minutes of contact
void Graph::infectAndTrace()
{
    //randomly infect one person
    int randIndex = rand() % vertices.size();
    vertex *infectedV = &vertices[randIndex];
    vertices[randIndex].infected = true;
    std::cout << "Infected: " << infectedV->name << "\nClose contacts:" << endl;
    
    //print close contacts
    for(adjVertex e : infectedV->adj)
    {
        if(e.weight > 15)
        {
            std::cout << e.v->name << "," << e.weight << endl;
        }
    }
    displayInfections();
}

//Randomly infects one person and with a given infection rate infects all contacts
void Graph::infectAndSpread(double rate)
{
    //randomly infect one person
    int randIndex = (rand() % vertices.size()) + 1;
    vertex *patient0 = &vertices[randIndex];
    patient0->infected = true;
    std::cout << "Infected: " << patient0->name << "\nSpread:" << endl;

    queue<vertex*> inQueue;
    inQueue.push(patient0);
    //infect others, adding new patients to queue
    while(inQueue.empty() == false)
    {
        vertex *v = inQueue.front();
        inQueue.pop();

        for(adjVertex e : v->adj)
        {
            if( (rand()%100) < rate*100)
            {
                inQueue.push(e.v);
                e.v->infected = true;
                std::cout << "Infected: " << e.v->name << " after spending " << e.weight << " minutes with " << v->name << "." << endl;
            }
        }

        rate /= 2;//cut infection rate in half every step away
    }
    displayInfections();
}

//Finds vertex of individual with given name
vertex *Graph::findVertex(std::string name)
{
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == name) {
            return &vertices[i];
        }
    }
    return NULL;
}

//Sets group ID of all individuals connected to given person
void Graph::DFSLabel(std::string person, int ID)
{
    vertex *root = findVertex(person);

    //adds root to stack
    stack<vertex*> stack;
    stack.push(root);

    while(!stack.empty())
    {
        vertex *v = stack.top();
        stack.pop();

        //vertex *v = findVertex(v1);
        if(!v->visited)
        {
            //sets ID
            v->groupID = ID;
            v->visited = true;
        }

        //adds neighbors to stack
        for(adjVertex edge: v->adj)
        {
            if(edge.v->visited == false)
            {
                stack.push(edge.v);
            }
        }
    }
}

//Sets "visited" member variable of every vertex to false
void Graph::unvisit()
{
    for(vertex v: vertices)
    {
        v.visited = false;
    }
}

//Determines if every vertex is visited
bool Graph::allVisited()
{
    for(vertex v : vertices)
    {
        if(!v.visited)
        {
            return false;
        }
    }
    return true;
}