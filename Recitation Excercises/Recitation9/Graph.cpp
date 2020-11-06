#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

//return a vertex in the vertices vector, if it exists
vertex* Graph::findVert(string toAdd) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i]->value == toAdd) {
            return vertices[i];
        }
    }
    return NULL;
}

//add a vertex to the vertices vector
void Graph::addVertex(string toAdd) {
    if (findVert(toAdd) == NULL) {
        vertices.push_back(new vertex(toAdd));
    }
}

//if both firstv & secondv are present in the graph, create an edge b/w them 
void Graph::addEdge(string firstv, string secondv) {
    vertex *fv = findVert(firstv);
    vertex *sv = findVert(secondv);
    if (!fv || !sv) {
        cout << "Either " << firstv << " or " << secondv << " not present in graph." << endl;
    } else {
        //detect duplicate edges (ugly way to do it but alas)
        for (int i = 0; i < fv->links.size(); i++) {
            if (fv->links[i]->neighbor->value == secondv) {
                return;
            }
        }
        edge *egg = new edge(sv);
        fv->links.push_back(egg);
        edge *eggo = new edge(fv);
        sv->links.push_back(eggo);
    }
}

//print all of the vertices in a graph & their neighbors
void Graph::print() {
    vertex *lilvert;
    for (int i = 0; i < vertices.size(); i++) {
        lilvert = vertices[i];
        cout << lilvert->value << ": ";
        for (int j = 0; j < lilvert->links.size(); j++) {
            cout << lilvert->links[j]->neighbor->value << " ";
        }
        cout << endl;
    }
}


vector Graph::BFS(string startVal, string endVal)
{
    vertex *v = search(startVal);
    v->visited = true;
    v->distance = 0;
    v->parent = nullptr;

    queue<vertex*> q;
    q.push(v);

    while(!q.empty())
    {
        vertex *n = q.front(); //front returns a value
        q.pop(); //remove from queue
        for(int x = 0; x < n->adj.size(); x++)
        {
            if(n->adj[x].v->visited == false)
            {
                n->adj[x].v->distance = n->distance+1;//parent distance +1
                n->adj[x].v->parent = n;
                //check if its what we're looking for
                if(n->adj[x].v->name == endVal)
                {
                    return n->adj[x].v;
                }
                else
                {
                    n->adj[x].v->visited = true;
                    q.push(n->adj[x].v);
                }
            }
        }
    }
    return nullptr;
}

void Graph::printBFSPath(string v1, string v2)
{
    vertex *v = BFS(v1, v2);
    std::cout << "Distance: " << v->distance << std::endl;
    while(v != nullptr)
    {
        cout << v->name << "<--";
        v = v->parent;
    }
    std::cout << std::endl;
}



//determines if path exists in a graph
bool Graph::pathExists(string path[], int length)
{
    vertex *v search(path[0]);
    v->visited = true;
    v->distance = 0;
    v->parent = nullptr;

    queue<vertex*> q;
    q.push(v);
    int step = 1;
    while(!q.empty())
    {
        bool found = false;
        vertex *n = q.front(); //front returns a value
        q.pop(); //remove from queue
        for(int x = 0; x < n->adj.size(); x++)
        {
            if(n->adj[x].v->name == path[step])
            {
                n->adj[x].v->distance = n->distance+1;//parent distance +1
                n->adj[x].v->parent = n;
                //check if its what we're looking for
                q.push(n->adj[x].v);
                
                found = true;
            }
        }
        step++;
        if(found == false)
        {
            return false;
        }
    }
    return true;
}






//recursively traverse down the tree from the given vertex
//and print it very badly
void dfsRHelper(vertex *inV) {
    inV->visited = true;
    vertex *temp;
    for (int i = 0; i < inV->links.size(); i++) {
        temp = inV->links[i]->neighbor;
        if (!temp->visited) {
            cout << temp->value << endl;
            dfsRHelper(temp);
        }
    }
}

void Graph::dfsR(string value) {
    vertex *root = findVert(value);
    if (root != NULL) {
        cout << endl << root->value << endl;
        dfsRHelper(root);
    }
    cout << endl;
    unvisit();
}

//iteratively traverse through a graph from the given vertex
void Graph::dfsI(string value) {
    vertex *root = findVert(value);

    //adds root to stack
    stack<string> stack;
    stack.push(value);

    while(!stack.empty())
    {
        string v1 = stack.top();
        stack.pop();

        vertex *v = findVert(v1);
        if(v->visited == false)
        {
            //prints vertex
            std::cout << v->value << std::endl;
            v->visited = true;
        }

        //adds neighbors to stack
        for(edge* edge: v->links)
        {
            if(edge->neighbor->visited == false)
            {
                stack.push(edge->neighbor->value);
            }
        }
    }

    unvisit();
}

bool Graph::isThereAPath(string s1, string s2)
{
    vertex *root = findVert(s1);

    //adds root to stack
    stack<string> stack;
    stack.push(s1);

    while(!stack.empty())
    {
        string v1 = stack.top();
        stack.pop();

        vertex *v = findVert(v1);
        if(v->visited == false)
        {
            //determines if current vector has the desired string
            if(v->value == s2)
            {
                unvisit();
                std::cout << "Path found" << std::endl;
                return true;
            }
            v->visited = true;
        }

        //adds neighbors to stack
        for(edge* edge: v->links)
        {
            if(edge->neighbor->visited == false)
            {
                stack.push(edge->neighbor->value);
            }
        }
    }

    unvisit();
    std::cout << "Path not found" << std::endl;
    return false;
}

void Graph::unvisit() {
    for(vertex *v: vertices)
    {
        v->visited = false;
    }
}

int main() {
    Graph myGwaf;
    myGwaf.addVertex("A");
    myGwaf.addVertex("B");
    myGwaf.addVertex("C");
    myGwaf.addVertex("D");
    myGwaf.addVertex("E");
    myGwaf.addEdge("A", "B");
    myGwaf.addEdge("A", "C");
    myGwaf.addEdge("B", "C");
    myGwaf.addEdge("D", "E");

    myGwaf.dfsI("A");
    myGwaf.isThereAPath("A", "C"); //should pass
    myGwaf.isThereAPath("A", "D"); //should fail



    // ifstream lineStream("txtGraph.txt");
    // string val;
    // while(getline(lineStream, val)) {
    //     stringstream wordStream(val);

    //     while(getline(wordStream, curWord, ',')) {

    //     }

    // }
}