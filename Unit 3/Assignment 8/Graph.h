Reci#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
};

struct vertex{
    std::string name;
    int groupID;
    vertex *parent;
    bool visited;
    int distance;
    bool infected;
    std::vector<adjVertex> adj;
};

class Graph
{
    public:
        Graph(){};  
        ~Graph(){}; 
        void addEdge(std::string v1, std::string v2, int weight);
        void addVertex(std::string name);
        int isAdjacent(std::string v1, std::string v2);
        void displayEdges();
        void assignGroupID();
        void infectAndTrace();
        void infectAndSpread(double rate);
        
        
    protected:
    private:
        std::vector<vertex> vertices;
        vertex *findVertex(std::string name);
        void DFSLabel(std::string person, int ID);
        void unvisit();
        bool allVisited();
        
};

#endif // GRAPH_H
