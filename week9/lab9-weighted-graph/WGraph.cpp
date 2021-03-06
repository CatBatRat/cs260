//
//  Graph.cpp
//  Example Non-directed, non-weighted graph
//
//  Created by Jim Bailey on 11/25/17.
//  Licensed under a Creative Commons Attribution 4.0 International License.
//

#include "WGraph.hpp"

// for exception handling
#include <stdexcept>

// to create formatted strings to return
#include <iomanip>
#include <sstream>

// for breadth first and depth first traversals
#include <queue>
#include <stack>
#include <list>

#include <iostream>

/*
 * definitions here for reference
 *
struct Edge
{
    int startIndex;
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
WGraph::WGraph()
{
  // initialize number of nodes in list
  numNodes = 0;

  // initialize nodeList to nullptrs
  for (int i = 0; i < SIZE; i++)
    nodeList[i] = nullptr;

  // set up edge Matrix to start with no edges
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      edgeMatrix[i][j] = 0;
}

// destructor
WGraph::~WGraph()
{
  // delete all connections from each node in nodeList
  for (int i = 0; i < numNodes; i++)
  {
    // similar to destructor on linked list
    Edge *ptr = nodeList[i]->connects;
    while (ptr != nullptr)
    {
      Edge *temp = ptr;
      ptr = ptr->next;
      delete temp;
    }
  }
}

// add a new node to the graph
// only failure is if graph arrays are full
void WGraph::addNode(char name)
{
  // alternately, double the size of everything and start over
  if (numNodes >= SIZE)
    throw std::overflow_error("Graph size exceeded!!");

  // create a node with this name
  // initialize it with no edges and not yet visited
  Node *temp = new Node;
  temp->name = name;
  temp->visited = false;
  temp->connects = nullptr;

  // add to the list of nodes in graph
  nodeList[numNodes++] = temp;
}

// add a new edge to the graph
// return false and do nothing if either end is invalid
// otherwise add to both nodes edge lists and to the matrix
bool WGraph::addWEdge(char starts, char ends, int weight)
{
  if (starts == ends)
    return false;

  int startIndex = findNode(starts);
  int endIndex = findNode(ends);

  if (startIndex == -1 || endIndex == -1)
    return false;

  // set both links in edgeMatrix
  edgeMatrix[startIndex][endIndex] = weight;
  edgeMatrix[endIndex][startIndex] = weight;

  // create two new edges (one for each direction)
  // and add one to each nodes list of edges
  // each end also knows where it came from so
  // when working with edges it is easy to get
  // the source node when traversing
  Edge *startEnd = new Edge;
  startEnd->startIndex = startIndex;
  startEnd->endIndex = endIndex;
  startEnd->weight = weight;
  startEnd->next = nodeList[startIndex]->connects;
  nodeList[startIndex]->connects = startEnd;

  Edge *endStart = new Edge;
  endStart->startIndex = endIndex;
  endStart->endIndex = startIndex;
  endStart->weight = weight;
  endStart->next = nodeList[endIndex]->connects;
  nodeList[endIndex]->connects = endStart;

  return true;
}

// linear search for a node with this name
// return -1 if not found
// otherwise return its index in the nodeList
int WGraph::findNode(char name)
{
  for (int i = 0; i < numNodes; i++)
    if (nodeList[i]->name == name)
      return i;
  return -1;
}

// listing of nodes in the order
// they were added to the graph
std::string WGraph::listNodes()
{
  std::string theList = "";
  for (int i = 0; i < numNodes; i++)
  {
    theList += nodeList[i]->name;
    theList += " ";
  }
  return theList;
}

// for each node in graph,
// display its edges, using the edgelist
std::string WGraph::displayWEdges()
{
  std::stringstream ss;
  for (int i = 0; i < numNodes; i++)
  {
    // add the node name to the display
    ss << nodeList[i]->name;
    ss << "-";

    // walk down its list of edges and add them also
    Edge *ptr = nodeList[i]->connects;
    while (ptr != nullptr)
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
std::string WGraph::displayWMatrix()
{
  std::stringstream ss;

  // output header line of destinations
  ss << std::setw(2) << " ";
  for (int i = 0; i < numNodes; i++)
  {
    ss << std::setw(4) << nodeList[i]->name;
  }
  ss << std::endl;

  // now output the array
  for (int i = 0; i < numNodes; i++)
  {
    // add the starting node
    ss << std::setw(2) << nodeList[i]->name;

    // now add its connections
    for (int j = 0; j < numNodes; j++)
      ss << std::setw(4) << edgeMatrix[i][j];

    // end the row
    ss << std::endl;
  }
  return ss.str();
}

// helper function to reset all nodes to not visited
void WGraph::resetVisited()
{
  for (int i = 0; i < numNodes; i++)
    nodeList[i]->visited = false;
}

// breadth first traversal starting at the index of a node in the nodeList
// >>array determined by a char value input as the argument
std::string WGraph::breadthFirst(char start)
{
  // create a ostringstream for output
  std::ostringstream out;
  // create the queue
  std::queue<Node *> bf;
  // find location of first node
  int loc = findNode(start);
  // check if valid location
  if (loc < 0)
  {
    out << "||" << start << " does not exist. Please enter a valid node.||";
    return out.str();
  }
  // get pointer for the current node using index from `findNode`
  Node *ptr = nodeList[loc];
  // push node onto queue and set it as visited
  bf.push(ptr);
  ptr->visited = true;
  out << "Breadth First Traversal starting at " << start << "\n";
  // input data from first node to the string ouput object
  out << ptr->name << " :";
  // while the queue is not empty
  while (!bf.empty())
  {
    // capture pointer of first item in the queue
    ptr = bf.front();
    // pop item from the queue
    bf.pop();
    // pointer to link list of edges connecting to this node
    for (Edge *edge = ptr->connects; edge; edge = edge->next)
    {
      // next node in graph using index from `connects` to find
      // corisponding node in nodeList
      ptr = nodeList[edge->endIndex];
      // if node has not been visited
      if (ptr->visited == false)
      {
        // add name to output string
        out << " " << ptr->name;
        // set to visited
        ptr->visited = true;
        // push onto the queue
        bf.push(ptr);
      }
      // next connected edge
    }
  }
  // reset all not visisted
  resetVisited();
  return out.str();
}

std::string WGraph::depthFirst(char start)
{
  // create a ostringstream for output
  std::ostringstream out;
  // create the stack
  std::stack<Node *> df;
  // find location of first node
  int loc = findNode(start);
  // check if valid location
  if (loc < 0)
  {
    out << "||" << start << " does not exist. Please enter a valid node.||";
    return out.str();
  }
  // get pointer for the current node using index from `findNode`
  Node *ptr = nodeList[loc];
  // push node onto stack and set it as visited
  df.push(ptr);
  ptr->visited = true;
  out << "Depth First Traversal starting at " << start << "\n";
  // input data from first node to the string ouput object
  out << ptr->name << " :";
  // while the stack is not empty
  while (!df.empty())
  {
    // capture pointer of first item in the stack
    ptr = df.top();
    // pop top item from the stack
    df.pop();
    // pointer to link list of edges connecting to this node
    for (Edge *edge = ptr->connects; edge; edge = edge->next)
    {
      // next node in graph using index from connects to find
      // corisponding node in nodeList
      Node *otherEnd = nodeList[edge->endIndex];
      // if node has not been visited
      if (otherEnd->visited == false)
      {
        // push both the current and the otherEnd on the stack
        df.push(ptr);
        df.push(otherEnd);
        // set otherEnd to visited
        otherEnd->visited = true;
        // input otherEnd value to output object
        out << " " << otherEnd->name;
        // break
        break;
      }
    }
  }
  resetVisited();
  return out.str();
}

std::string WGraph::minCostTree(char start)
{
  // create a ostringstream for output
  std::ostringstream out;
  // create a stack to act as a priority queue
  std::list<Edge *> mct;
  int loc = findNode(start);
  // check if node was found before continuing
  Node *ptr = (loc > -1) ? nodeList[loc] : nullptr;
  if(!ptr) return "Provided node does not exist.";
  ptr->visited = true;
  for (Edge *edge = ptr->connects; edge; edge = edge->next)
  {
    mct.push_back(edge);
  }
  while (!mct.empty())
  {
    Edge *shortest = getShortestEdge(mct);
    ptr = nodeList[shortest->endIndex];
    ptr->visited = true;
    out << nodeList[shortest->startIndex]->name << /*"-" << shortest->weight <<*/ "-" << nodeList[shortest->endIndex]->name << " ";
    for (Edge *edge = ptr->connects; edge; edge = edge->next)
    {
      addQueue(edge, mct);
    }
  }
  resetVisited();
  return out.str();
}

Edge *WGraph::getShortestEdge(std::list<Edge *> &edges)
{
  Edge *shortest = edges.front();
  for (auto const &e : edges)
  {
    if (e->weight < shortest->weight)
    {
      shortest = e;
    }
  }
  edges.remove(shortest);
  return shortest;
}

void WGraph::addQueue(Edge *edge, std::list<Edge *> &edges)
{
  if (nodeList[edge->endIndex]->visited == false)
  {
    for (auto &old : edges)
    {
      if (edge->endIndex == old->endIndex)
      {
        if (edge->weight < old->weight)
        {
          old = edge;
          return;
        }
      }
    }
    edges.push_front(edge);
    return;
  }
}