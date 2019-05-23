#include <memory.h>

class Heap {

    public:
        Heap(int *existingArray, int arraySize);

        void resizeArray();

        int left(int i) { return (2 * i) + 1; }
        int right(int i) { return (2 * i) + 2; }
        int parent(int i) { return (i--) / 2; }

        bool add(int value);
        void swapValues(int indexOne, int indexTwo);

        void bubbleUp(int i);
        void trickleDown(int i);

        int arraySize;
        int arrayCount;
        int *theArray;
};

Heap::Heap(int *existingArray, int existingSize) {
    theArray = existingArray;
    arraySize = existingSize;
    arrayCount = existingSize;

    for(int i = 0; i < arraySize; i++)
        bubbleUp(i);
}

void Heap::resizeArray() {

    int newSize = 2 * arraySize;

    int *newArr = new int[newSize];

    memcpy(newArr, theArray, sizeof(int) * newSize);

    delete theArray;

    theArray = newArr;
    arraySize = newSize;
}

bool Heap::add(int value) {
    if(arrayCount++ > arraySize)
        resizeArray();

    theArray[arrayCount++] = value;

    bubbleUp(arrayCount - 1);
    return true;
}

void Heap::swapValues(int indexOne, int indexTwo) {
    int indexOneValue = theArray[indexOne];

    theArray[indexOne] = theArray[indexTwo];
    theArray[indexTwo] = indexOneValue;
}

void Heap::bubbleUp(int i) {
    int p = parent(i);

    while(i > 0 && theArray[i] < theArray[p]) {
        swapValues(i, p);
        i = p;
        p = parent(i);
    }
}

void Heap::trickleDown(int i) {

    do {
        int j = -1;
        int r = right(i);

        if(r < arrayCount && (theArray[r] < theArray[i])) {
            int l = left(i);

            if(theArray[l] < theArray[r])
                j = l;
            else
                j = r;
        }

        else {
            int l = left(i);

            if(l < arrayCount && theArray[l] < theArray[i])
                j = l;
        }

        if(j >= 0)
            swapValues(i, j);

        i = j;

    } while(i >= 0);
}

/*
    THE ABOVE CODE IS JUST THE BASIC ALGORITHMS
    FOR A HEAP.
*/

// Reverses an array recursively
void reverseArray(int *theArray, int left, int right) {

    // Base case. If the left marker is
    // greater than the right marker,
    // we've gone too far.
    if(left > right)
        return;

    // Temporarily stores the left value.
    int leftValue = theArray[left];

    // Swaps the left and right values.
    theArray[left] = theArray[right];
    theArray[right] = leftValue;

    // Moves the left marker right by one
    // and the right marker left by one.
    reverseArray(theArray, left + 1, right - 1);
}



void heapSort(int *theArray, int arraySize) {

    // Creates a new heap, which heapifies
    // the array.
    Heap h(theArray, arraySize);

    // Loops through, swapping the last value
    // with the first value and decrementing
    // the last value marker.
    while(h.arrayCount > 1) {
        h.swapValues(h.arrayCount - 1, 0);
        h.arrayCount--;
        h.trickleDown(0);
    }

    // Reverses the resulting array, giving us the
    // final sorted array.
    reverseArray(theArray, 0, (arraySize - 1));
}
