#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
using namespace std;

class Edge
{
public:
    int endIndex;
    Edge* next;

};
class Node
{
public:
    char value;
    bool visited = false;
    Edge* edges = nullptr;

};
struct Link
{
    Node node;
    Link* next;
    Link* prev;
};
class Graph
{
    public:
        Graph();
        ~Graph();
        void addNode(char letter);
        bool addEdge (char start, char finish);
        string listNodes();
        string displayEdges();
        string breadthFirst(char value);
        string depthFirst (char value);
        void pushFIFO(Node node);
        Node popFIFO();
        void pushLIFO(Node node);
        Node popLIFO();
        string displayMatrix();
    protected:

    private:
        static const int SIZE = 30;
        int numNodes = 0;
        Node nodeList[SIZE];
        char edgeMatrix[SIZE][SIZE];
        int findNode(char value);
        void resetFalse();
        Link* FIFO = nullptr;
        Link* FIFOtail = nullptr;
        Link* LIFO = nullptr;

};

#endif // GRAPH_H
