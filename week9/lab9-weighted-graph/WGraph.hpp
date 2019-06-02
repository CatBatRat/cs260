//
//  Graph.hpp
//  Example Non-directed, non-weighted graph
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#ifndef WGRAPH_H
#define WGRAPH_H

#include <string>
#include <list>

struct Edge
{
    int endIndex;
    int weight;
    Edge * next;
};

struct Node
{
    char name;
    bool visited;
    Edge * connects;
};


class WGraph
{
    public:
        WGraph();
        virtual ~WGraph();

        void addNode(char name);
        bool addWEdge(char starts, char ends, int weight);

        std::string listNodes();
        std::string displayWEdges();
        std::string displayWMatrix();
        std::string depthFirst(char start);
        std::string breadthFirst(char start);
        std::string minCostTree(char start);


    private:
        static const int SIZE = 20;
        int numNodes;
        Node * nodeList[SIZE];
        int edgeMatrix[SIZE][SIZE];

        int findNode(char name);
        Edge *getShortestEdge(std::list<Edge *> &edges);
        Edge *ifEndMatch(Edge const *edge, std::list<Edge *> const &edges);
        void resetVisited();
};

#endif // GRAPH_H
