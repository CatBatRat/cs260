//
//  Graph.cpp
//  Example Non-directed, non-weighted graph
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "Graph.hpp"

// for exception handling
#include <stdexcept>

// to create formatted strings to return
#include <sstream>
#include <iomanip>

// for breadth first and depth first traversals
#include <queue>
#include <stack>

/*
 * definitions here for reference
 *
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
 *
 */

    // constructor
Graph::Graph()
{
        // initialize number of nodes in list
    numNodes = 0;

        // initialize nodeList to nullptrs
    for(int i = 0; i < SIZE; i++)
        nodeList[i] = nullptr;

        // set up edge Matrix to start with no edges
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            edgeMatrix[i][j] = 0;
}

    // destructor
Graph::~Graph()
{
    // delete all connections from each node in nodeList
    for(int i = 0; i < numNodes; i++)
    {
            // similar to destructor on linked list
        Edge * ptr = nodeList[i]->connects;
        while(ptr != nullptr)
        {
            Edge * temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
}

    // add a new node to the graph
    // only failure is if graph arrays are full
void Graph::addNode(char name)
{
        // alternately, double the size of everything and start over
    if( numNodes >= SIZE )
        throw std::overflow_error("Graph size exceeded!!");

        // create a node with this name
        // initialize it with no edges and not yet visited
    Node * temp = new Node;
    temp->name = name;
    temp->visited = false;
    temp->connects = nullptr;

        // add to the list of nodes in graph
    nodeList[numNodes++] = temp;
}


    // add a new edge to the graph
    // return false and do nothing if either end is invalid
    // otherwise add to both nodes edge lists and to the matrix
bool Graph::addEdge(char starts, char ends)
{
    if ( starts == ends )
        return false;

    int startIndex = findNode(starts);
    int endIndex = findNode(ends);

    if ( startIndex == -1 or endIndex == -1 )
        return false;

        // set both links in edgeMatrix
    edgeMatrix[startIndex][endIndex] = 1;
    edgeMatrix[endIndex][startIndex] = 1;

        // create two new edges (one for each direction)
        // and add one to each nodes list of edges
    Edge * startEnd = new Edge;
    startEnd->endIndex = endIndex;
    startEnd->next = nullptr;
    startEnd->next = nodeList[startIndex]->connects;
    nodeList[startIndex]->connects = startEnd;

    Edge * endStart = new Edge;
    endStart->endIndex = startIndex;
    endStart->next = nullptr;
    endStart->next = nodeList[endIndex]->connects;
    nodeList[endIndex]->connects = endStart;

    return true;
}


    // linear search for a node with this name
    // return -1 if not found
    // otherwise return its index in the nodeList
int Graph::findNode(char name)
{
    for(int i = 0; i < numNodes; i++)
        if ( nodeList[i]->name == name )
            return i;
    return -1;
}


    // listing of nodes in the order
    // they were added to the graph
std::string Graph::listNodes()
{
    std::string theList = "";
    for(int i = 0; i < numNodes; i++)
    {
        theList += nodeList[i]->name;
        theList += " ";
    }
    return theList;
}


    // for each node in graph,
    // display its edges, using the edgelist
std::string Graph::displayEdges()
{
    std::stringstream ss;
    for(int i = 0; i < numNodes; i++)
    {
            // add the node name to the display
        ss << nodeList[i]->name;
        ss << "-";

            // walk down its list of edges and add them also
        Edge * ptr = nodeList[i]->connects;
        while ( ptr != nullptr )
        {
            ss << nodeList[ptr->endIndex]->name;
            ss << " ";
            ptr = ptr->next;
        }
            // end this line of output
        ss << std::endl;
    }
    return ss.str();
}


    // display the adjacency matrix
    // as 0 for no connection and 1 for connection
std::string Graph::displayMatrix()
{
    std::stringstream ss;

        // output header line of destinations
    ss << std::setw(2) << " ";
    for(int i = 0; i < numNodes; i++)
        ss << std::setw(4) << nodeList[i]->name;
    ss << std::endl;

        // now output the array
    for(int i = 0; i < numNodes; i++)
    {
            // add the starting node
        ss << std::setw(2) << nodeList[i]->name;

            // now add its connections
        for(int j = 0; j < numNodes; j++)
            ss << std::setw(4) << edgeMatrix[i][j];

            // end the row
        ss << std::endl;
    }
    return ss.str();
}

// depth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string Graph::depthFirst(char name)
{
    std::string buffer = "Depth first traversal starting at ";
    buffer += name;
    buffer += "\n";

    Node *startingNode = nullptr;

    int index = findNode(name);

    // Returns an empty string if the node
    // wasn't found.
    if(index == -1)
        return "";

    startingNode = nodeList[index];

    std::stack<Node *> LIFO;

    LIFO.push(startingNode);

    startingNode->visited = true;

    buffer += startingNode->name;
    buffer += " : ";

    while(!LIFO.empty()) {

        Node *currentNode = LIFO.top();

        LIFO.pop();

        for(Edge *ptr = currentNode->connects; ptr != nullptr; ptr = ptr->next) {
            Node *otherEnd = nodeList[ptr->endIndex];

            if(!otherEnd->visited) {
                LIFO.push(currentNode);
                LIFO.push(otherEnd);

                buffer += otherEnd->name;
                buffer += " ";

                otherEnd->visited = true;
                break;
            }
        }
    }

    return buffer;
}

// breadth first traversal
// starts at a given node
// outputs a list of nodes visited
// and a list of any unreached nodes
std::string Graph::breadthFirst(char name)
{
    std::string buffer = "Breadth first traversal starting at ";
    buffer += name;
    buffer += "\n";

    Node *startingNode = nullptr;

    int index = findNode(name);

    // Returns an empty string if the node
    // wasn't found.
    if(index == -1)
        return "";

    startingNode = nodeList[index];

    std::queue<Node *> FIFO;

    FIFO.push(startingNode);

    startingNode->visited = true;

    // Pretty formatting for the start of
    // the list.
    buffer += startingNode->name;
    buffer += " : ";

    while(!FIFO.empty()) {

        Node *currentNode = FIFO.front();

        FIFO.pop();

        for(Edge *ptr = currentNode->connects; ptr != nullptr; ptr = ptr->next) {

            Node *otherEnd = nodeList[ptr->endIndex];

            if(!otherEnd->visited) {

                FIFO.push(otherEnd);

                buffer += otherEnd->name;
                buffer += " ";

                otherEnd->visited = true;
            }
        }
    }

    resetVisited();

    buffer += "\n";

    return buffer;
}

    // helper function to reset all nodes to not visited
void Graph::resetVisited()
{
    for(int i = 0; i < numNodes; i++)
        nodeList[i]->visited = false;
}


