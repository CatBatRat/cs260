#include <iostream>

#include "GRAPH.H"

using namespace std;

int main()
{
    Graph tree;

    tree.addNode('A');
    tree.addNode('C');
    tree.addNode('T');
    tree.addNode('Z');
    tree.addNode('X');
    tree.addNode('K');
    tree.addNode('Q');
    tree.addNode('J');
    tree.addNode('M');
    tree.addNode('U');

    cout << tree.listNodes() << endl << endl;

    tree.addEdge('A', 'C');
    tree.addEdge('A', 'T');
    tree.addEdge('A', 'Z');
    tree.addEdge('X', 'C');
    tree.addEdge('C', 'K');
    tree.addEdge('T', 'Q');
    tree.addEdge('K', 'Q');
    tree.addEdge('Q', 'J');
    tree.addEdge('J', 'M');
    tree.addEdge('Z', 'X');

    cout << tree.displayEdges() << endl << endl;
    cout << tree.displayMatrix() << endl << endl;

    cout << tree.breadthFirst('Q') << endl << endl;

    cout << tree.depthFirst('Q') << endl << endl;

    return 0;
}
