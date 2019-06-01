//
//  Graph.hpp
//  Example Non-directed, non-weighted graph
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <string>

struct Edge
{
    int endIndex;
    Edge * next;
};

struct Node
{
    char name;
    bool visited;
    Edge * connects;
};


class Graph
{
    public:
        Graph();
        virtual ~Graph();

        void addNode(char name);
        bool addEdge(char starts, char ends);

        std::string listNodes();
        std::string displayEdges();
        std::string displayMatrix();

        std::string breadthFirst(char name);
        std::string depthFirst(char name);

    private:
        static const int SIZE = 20;
        int numNodes;
        Node * nodeList[SIZE];
        int edgeMatrix[SIZE][SIZE];

        int findNode(char name);
        void resetVisited();
};

#endif // GRAPH_H
