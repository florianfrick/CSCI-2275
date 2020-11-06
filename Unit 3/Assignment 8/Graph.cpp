#include "Graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

Graph::Graph()
{
}
Graph::~Graph()
{
    //dtor
}
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
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);
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
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}


int Graph::isAdjacent(std::string v1, std::string v2)
{
    // vertex *root = findVertex(v1);

    // //adds root to stack
    // stack<string> stack;
    // stack.push(v1);

    // while(!stack.empty())
    // {
    //     string v1 = stack.top();
    //     stack.pop();

    //     vertex *v = findVertex(v1);
    //     if(v->visited == false)
    //     {
    //         //determines if current vector has the desired string
    //         if(v->name == v2)
    //         {
    //             unvisit();
    //             std::cout << "Path found" << std::endl;
    //             return true;
    //         }
    //         v->visited = true;
    //     }

    //     //adds neighbors to stack
    //     for(adjVertex edge: v->adj)
    //     {
    //         if(edge->v->visited == false)
    //         {
    //             stack.push(edge->v->name);
    //         }
    //     }
    // }

    // unvisit();
    // std::cout << "Path not found" << std::endl;
    return false;
}

void Graph::assignGroupID()
{
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
}

void Graph::infectAndTrace()
{
    //randomly infect one person
    int randIndex = (rand() % vertices.size()) + 1;
    vertex infected = vertices[randIndex];
    infected.infected = true;

    cout << "Infected: " << infected.name << "\n Close contacts:" << endl;
    //print close contacts
    for(adjVertex e : infected.adj)
    {
        if(e.weight > 15)
        {
            cout << e.v->name << "," << e.weight << endl;
        }
    }
}

void Graph::infectAndSpread(double rate)
{
    //randomly infect one person
    int randIndex = (rand() % vertices.size()) + 1;
    vertex patient0 = vertices[randIndex];
    patient0.infected = true;

    queue<vertex> inQueue;
    inQueue.push(patient0);
    //infect others, adding new patients to queue
    while(inQueue.empty() == false)
    {
        vertex v = inQueue.front();
        inQueue.pop();

        for(adjVertex e : v.adj)
        {
            if(rand() < rate)
            {
                inQueue.push(*(e.v));
                e.v->infected = true;
                cout << "Infected: " << e.v->name << " after spending " << e.weight << " minutes with " << v.name << "." << endl;
            }
        }

        rate /= 2;//cut infection rate in half every step away
    }
}

vertex *Graph::findVertex(std::string name)
{
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i].name == name) {
            return &vertices[i];
        }
    }
    return NULL;
}

void Graph::DFSLabel(std::string person, int ID)
{
    vertex *root = findVertex(person);

    //adds root to stack
    stack<string> stack;
    stack.push(person);

    while(!stack.empty())
    {
        string v1 = stack.top();
        stack.pop();

        vertex *v = findVertex(v1);
        if(v->visited == false)
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
                stack.push(edge.v->name);
            }
        }
    }
}

void Graph::unvisit()
{
    for(vertex v: vertices)
    {
        v.visited = false;
    }
}

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