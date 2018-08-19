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
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <list>
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
    vector<int> bfs();
    void bfsHelper(vector<Vertex*>& nodes, vector<int>& ret, unordered_map<Vertex*, bool>& visited, int idx);
    vector<int> dfs();
    void dfsHelper(Vertex* node, vector<int>& ret, unordered_map<Vertex*, bool>& visited);
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

vector<int> Graph::bfs()
{
    /* time complexity for bfs is: O(V+E) */
    vector<int> bfs_order;
    unordered_map<Vertex*, bool> visited;
    /* this case focus on the undisconnected graph */
    for(int i = 0; i < this->getSize(); ++i)
    {
        if(visited.find(this->getNodes()[i]) == visited.end())
            bfsHelper(this->nodes, bfs_order, visited, i);
    }
    return bfs_order;
}

void Graph::bfsHelper(vector<Vertex*>& nodes, vector<int>& ret, unordered_map<Vertex*, bool>& visited, int idx)
{
    if(visited.find(nodes[idx]) != visited.end())
        return;
    visited[nodes[idx]] = true;
    ret.push_back(nodes[idx]->getId());
    queue<Vertex*> q;
    q.push(nodes[idx]);
    
    while(!q.empty())
    {
        Vertex* v = q.front();
        q.pop();
        vector<Vertex*> neighbors = v->getNeighbors();
        for(int i = 0; i < neighbors.size(); ++i)
        {
            if(visited.find(neighbors[i]) != visited.end())
                continue;
            int id = neighbors[i]->getId();
            ret.push_back(id);
            visited[neighbors[i]] = true;
            q.push(neighbors[i]);
        }
    }
    return;
}

vector<int> Graph::dfs()
{
    /* time complexity for dfs is O(V+E) */
    vector<int> ret;
    unordered_map<Vertex*, bool> visited;
    /* if there are undisconnected graph, we can still cover with this for loop */
    for(Vertex* node : this->getNodes())
    {
        if(visited.find(node) == visited.end())
            dfsHelper(node, ret, visited);
    }
    return ret;
}

void Graph::dfsHelper(Vertex* node, vector<int>& ret, unordered_map<Vertex*, bool>& visited)
{
    if(visited.find(node) != visited.end())
        return;
    visited[node] = true;
    ret.push_back(node->getId());
    for(auto neighbor : node->getNeighbors())
    {
        if(visited.find(neighbor) != visited.end())
            continue;
        dfsHelper(neighbor, ret, visited);
    }
    return;
}

int main(int argc, const char * argv[]) {
    
    /* create graph */
    /***********************
     the graph as following:
     
               1
              / \
             /   \
            2     3
            |\    |
            | \   |
            |  \  |
            |   \ |
            |    \|
            4-----5
             \   /
              \ /
               6
     ************************/
    
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);
    Vertex* v6 = new Vertex(6);
    
    v1->addNeighbors(v2);
    v1->addNeighbors(v3);
    v2->addNeighbors(v4);
    v2->addNeighbors(v5);
    v2->addNeighbors(v1);
    v3->addNeighbors(v1);
    v3->addNeighbors(v5);
    v4->addNeighbors(v2);
    v4->addNeighbors(v5);
    v4->addNeighbors(v6);
    v5->addNeighbors(v2);
    v5->addNeighbors(v3);
    v5->addNeighbors(v4);
    v5->addNeighbors(v6);
    v6->addNeighbors(v4);
    v6->addNeighbors(v5);
 
    Graph* g1 = new Graph();
    g1->addNodes(v1);
    g1->addNodes(v2);
    g1->addNodes(v3);
    g1->addNodes(v4);
    g1->addNodes(v5);
    g1->addNodes(v6);
    
    vector<int> bfs_travel = g1->bfs();
    for(auto e: bfs_travel)
        cout<<e<<" ";
    cout<<endl;
    
    vector<int> dfs_travel = g1->dfs();
    for(auto e: dfs_travel)
        cout<<e<<" ";
    cout<<endl;
    return 0;
}
