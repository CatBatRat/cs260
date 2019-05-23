//
//  main.cpp
//  HeapSort Lab
//
//  Created by Jim Bailey on 5/15/19.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "heapsort.hpp"

using namespace std;

// generic display method
void display(int theArray[], int length);
// load array with random numbers
void init(int theArray[], int length);

int main()
{
    // create the array
    const int SIZE = 20;
    int * values = new int[SIZE];

    // initialize it with random numbers
    init(values, SIZE);

    cout << "The unsorted data is " << endl;
    display(values, SIZE);

    // sort it
    heapSort(values, SIZE);

    cout << "The sorted data is " << endl;
    display(values, SIZE);

    return 0;
}

// generic display method
void display(int theArray[], int length)
{
    const int LINE_LEN = 10;
    const int NUM_WID = 4;

    for(int i = 0; i < length; i++)
    {
        cout << setw(NUM_WID) << theArray[i];
        if ( (i+1) % LINE_LEN == 0 )
            cout << endl;
    }
    cout << endl;
}

// load array with random numbers
void init(int theArray[], int length)
{
    srand(static_cast<int>(time(NULL)));

    const int MAX = 99;
    const int MIN = 1;

    for(int i = 0; i < length; i++)
        theArray[i] = rand() % MAX + MIN;
}
