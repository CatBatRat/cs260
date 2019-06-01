#include "Graph.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Graph::Graph()
{
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            edgeMatrix[i][j] = 0;
}

Graph::~Graph()
{
    for (int i = 0; i < numNodes; i++)
    {
        Edge* ptr = nodeList[i].edges;
        while(ptr != nullptr)
        {
            Edge* temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }
}

void Graph::addNode(char letter)
{
    if (numNodes >= SIZE)
    {
        throw out_of_range("Too many nodes!");
    }
    Node* temp = new Node;
    temp->value = letter;
    temp->visited = false;
    temp->edges = nullptr;
    nodeList[numNodes++] = *temp;
}
bool Graph::addEdge (char start, char finish)
{

    if(start == finish)
        return false;

    int startIndex = findNode(start);
    int endIndex = findNode(finish);
    if(startIndex == -1 or endIndex == -1)
        return false;

    edgeMatrix[startIndex][endIndex] = 1;
    edgeMatrix[endIndex][startIndex] = 1;

    Edge* startEnd = new Edge;
    startEnd->endIndex = endIndex;
    startEnd->next = nullptr;
    startEnd->next = nodeList[startIndex].edges;
    nodeList[startIndex].edges = startEnd;

    Edge* endStart = new Edge;
    endStart->endIndex = startIndex;
    endStart->next = nullptr;
    endStart->next = nodeList[endIndex].edges;
    nodeList[endIndex].edges = endStart;

    return true;
}
int Graph::findNode(char value)
{
    for(int i = 0; i < numNodes; i++)
    {
        if (nodeList[i].value == value)
            return i;
    }
    return -1;
}
string Graph::listNodes()
{
    string theList = "";
    for(int i = 0; i < numNodes; i++)
    {
        theList += nodeList[i].value;
        theList += " ";
    }
    return theList;
}
string Graph::displayEdges()
{
    string buffer = "";
    for(int i =0; i < numNodes; i++)
    {
        buffer += nodeList[i].value;
        buffer += "-";

        Edge* ptr = nodeList[i].edges;
        while (ptr != nullptr)
        {
            buffer += nodeList[ptr->endIndex].value;
            buffer += " ";
            ptr = ptr->next;
        }
        buffer += "\n";
    }
    return buffer;
}
string Graph::breadthFirst(char value)
{
    string buffer = "";
    int startIndex = findNode(value);
    nodeList[startIndex].visited = true;
    pushFIFO(nodeList[startIndex]);

    while(FIFO)
    {
        Node current = popFIFO();
        buffer = buffer + current.value + " ";
        Edge* ptr = current.edges;

        while (ptr != nullptr)
        {
            if(nodeList[ptr->endIndex].visited == false)
            {
                nodeList[ptr->endIndex].visited = true;
                pushFIFO(nodeList[ptr->endIndex]);
            }
            ptr = ptr->next;
        }
    }

    resetFalse();
    return buffer;
}

void Graph::pushFIFO(Node newNode)
{
    Link* temp = new Link;
    temp->node = newNode;
    temp->prev = FIFOtail;
    temp->next = nullptr;
    if(FIFOtail)
        FIFOtail->next = temp;
    FIFOtail = temp;
    if(!FIFO)
    {
        FIFO = FIFOtail;
    }
}

Node Graph::popFIFO()
{
    Link* linkTemp = FIFO;
    Node nodeTemp = linkTemp->node;
    FIFO = FIFO->next;

    delete linkTemp;
    if (FIFO == nullptr)
        FIFOtail = nullptr;

    return nodeTemp;
}

string Graph::depthFirst (char value)
{
    string buffer = "";
    int startIndex = findNode(value);
    nodeList[startIndex].visited = true;
    pushLIFO(nodeList[startIndex]);
    buffer = buffer + nodeList[startIndex].value + " ";


    while(LIFO)
    {
        Node current = LIFO->node;
        Edge* edge = current.edges;
        while(edge != nullptr)
        {
            if(nodeList[edge->endIndex].visited == false)
            {
                pushLIFO(nodeList[edge->endIndex]);
                buffer = buffer + nodeList[edge->endIndex].value + " ";
                nodeList[edge->endIndex].visited = true;
                edge = nodeList[edge->endIndex].edges;
            }
            else
                edge = edge->next;
        }
        popLIFO();
    }

    resetFalse();
    return buffer;
}
void Graph::pushLIFO(Node newNode)
{
    Link* tempLink = new Link;
    tempLink->node = newNode;
    tempLink->next = LIFO;
    tempLink->prev = nullptr;
    LIFO = tempLink;
}
Node Graph::popLIFO()
{
    Link* linkTemp = LIFO;
    Node nodeTemp = linkTemp->node;
    LIFO = LIFO->next;

    delete linkTemp;

    return nodeTemp;
}

void Graph::resetFalse()
{
    for(int i = 0; i < numNodes; i++)
        nodeList[i].visited = false;
}
std::string Graph::displayMatrix()
{
    std::stringstream ss;
    ss << "The edgeMatrix is: \n";

        // output header line of destinations
    ss << std::setw(2) << " ";
    for(int i = 0; i < numNodes; i++)
        ss << std::setw(4) << nodeList[i].value;
    ss << std::endl;

        // now output the array
    for(int i = 0; i < numNodes; i++)
    {
            // add the starting node
        ss << std::setw(2) << nodeList[i].value;

            // now add its connections
        for(int j = 0; j < numNodes; j++)
            ss << std::setw(4) << edgeMatrix[i][j];

            // end the row
        ss << std::endl;
    }
    return ss.str();
}
