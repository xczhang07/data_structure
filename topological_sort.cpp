//
//  main.cpp
//  Project1
//
//  Created by Xiaochong Zhang on 8/19/18.
//  Copyright © 2018 Xiaochong Zhang. All rights reserved.
//

//
//  main.cpp
//  Project1
//
//  Created by Xiaochong Zhang on 8/19/18.
//  Copyright © 2018 Xiaochong Zhang. All rights reserved.
//

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <list>
#include <stack>
using namespace std;


class Vertex
{
public:
    Vertex(int id);
    vector<Vertex*> getNeighbors();
    void addNeighbors(Vertex* v);
    int getId();
private:
    vector<Vertex*> neighbors;
    int id;
};


Vertex::Vertex(int id)
{
    this->id = id;
}

void Vertex::addNeighbors(Vertex* v)
{
    this->neighbors.push_back(v);
    return;
}

vector<Vertex*> Vertex::getNeighbors()
{
    return this->neighbors;
}

int Vertex::getId()
{
    return this->id;
}

class Graph
{
public:
    Graph();
    void addNodes(Vertex* node);
    vector<Vertex*> getNodes();
    size_t getSize();
private:
    vector<Vertex*> nodes;
};

Graph::Graph() {}

void Graph::addNodes(Vertex* node)
{
    this->nodes.push_back(node);
}

vector<Vertex*> Graph::getNodes()
{
    return this->nodes;
}

size_t Graph::getSize()
{
    return this->nodes.size();
}

void TopologicalSortUtil(Vertex* v, stack<int>& order, unordered_set<Vertex*>& visited)
{
    visited.insert(v);
    for(int i = 0; i < v->getNeighbors().size(); ++i)
    {
        Vertex* neighbor = v->getNeighbors()[i];
        if(visited.find(neighbor) == visited.end())
            TopologicalSortUtil(neighbor, order, visited);
    }
    order.push(v->getId());
    return;
}

/* we ust stack to implement the topological sort in this case
  which is different with using indegree method, topological sort
 only works on the Directed Acyclic Graph */
stack<int> TopologicalSort(Graph* graph)
{
    unordered_set<Vertex*> visited;
    stack<int> order;
    for(auto node : graph->getNodes())
    {
        if(visited.find(node) == visited.end())
            TopologicalSortUtil(node, order, visited);
    }
    return order;
}

/* this function implement the topological sort with indgree method */
vector<int> TopologicalSort2(Graph* graph)
{
    if(!graph) return {};
    vector<int> topo_order;
    // initialize the indegree map
    map<Vertex*, int> indegree;
    for(auto n: graph->getNodes())
        indegree[n] = 0;
    for(auto n: graph->getNodes())
    {
        for(auto v: n->getNeighbors())
            indegree[v]++;
    }
    // caculate the result
    while(!indegree.empty())
    {
        Vertex* curr = NULL;
        for(auto e: indegree)
        {
            if(e.second == 0)
            {
                topo_order.push_back(e.first->getId());
                curr = e.first;
                break;
            }
        }
        for(auto v: curr->getNeighbors())
            indegree[v]--;
        indegree.erase(curr);
    }
    return topo_order;
}

int main(int argc, const char * argv[]) {
    
    /* create a directed acyclic graph */
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);
    Vertex* v6 = new Vertex(6);

    v3->addNeighbors(v4);
    v4->addNeighbors(v2);
    v5->addNeighbors(v2);
    v5->addNeighbors(v1);
    v6->addNeighbors(v1);
    v6->addNeighbors(v3);
    
    Graph* g1 = new Graph();
    g1->addNodes(v1);
    g1->addNodes(v2);
    g1->addNodes(v3);
    g1->addNodes(v4);
    g1->addNodes(v5);
    g1->addNodes(v6);
    
    stack<int> topo_order = TopologicalSort(g1);
    while(!topo_order.empty())
    {
        cout<<topo_order.top()<<" ";
        topo_order.pop();
    }
    cout<<endl;
    vector<int> toplogical_sort = TopologicalSort2(g1);
    for(int i = 0; i < toplogical_sort.size(); ++i)
        cout<<toplogical_sort[i]<<" ";
    
    cout<<endl;
    return 0;
}
