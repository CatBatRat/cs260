#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "Heap.h"

Heap::Heap(int newSize) {
    arr = (newSize <= 0) ? new int[16] : new int[newSize];
    size = (newSize <= 0) ? 16 : newSize;

    count = 0;
}

// Gets the left child of a node
int Heap::left(int index) {
    return (2 * index) + 1;
}

// Gets the right child of a node
int Heap::right(int index) {
    return (2 * index) + 2;
}

// Gets the parent of a node
int Heap::parent(int index) {
    return (index - 1) / 2;
}

// Removes a value from the heap and returns it
int Heap::remove() {

    // Throws an error if the heap is empty
    if(count <= 0)
        throw std::length_error("The heap is empty!");

    int value = *arr;

    count--;

    // Sets the value at index 0 to the final value
    arr[0] = arr[count];

    // Sorts the heap again
    trickleDown(0);

    return value;
}

// Doubles the size of the array
void Heap::resize() {

    int newSize = 2 * size;

    int *newArr = new int[newSize];

    memcpy(newArr, arr, sizeof(int) * newSize);

    delete arr;

    arr = newArr;
    size = newSize;
}

// Inserts a new value into the heap
void Heap::insert(int value) {

    // Resizes if the array is full
    if(count >= size)
        resize();

    arr[count] = value;

    // Sorts the array afterwards, starting
    // from the bottom
    bubbleUp(count);

    count++;
}

// Sorts from the given node up.
void Heap::bubbleUp(int index) {

    // Base case
    if(index == 0)
        return;

    // If the parent's value is smaller, swap
    // them since this is a max heap and values
    // towards the top are larger
    if(arr[parent(index)] < arr[index]) {

        swap(parent(index), index);

        bubbleUp(parent(index));
    }

    else
        return;
}

// Swaps one value with another in the array
void Heap::swap(int indexOne, int indexTwo) {

    int value = arr[indexOne];

    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = value;
}

// Sorts the array from the given node down.
void Heap::trickleDown(int index) {

    // If this is true, this node is either
    // completely incorrect or it's the location
    // where a child node should be when added.
    if(left(index) >= count)
        return;

    if(right(index) >= count) {

        // If the child element of the current 'node'
        // is larger, swap the parent and the child
        if(arr[left(index)] > arr[index]) {

            swap(left(index), index);
            trickleDown(left(index));
        }

    }
    else {

        // Swaps the left value with it's parent if the parent
        // is smaller
        if(arr[left(index)] > arr[right(index)]) {

            if(arr[left(index)] > arr[index]) {

                swap(left(index), index);
                trickleDown(left(index));
            }

            trickleDown(left(index));
        }

        // Otherwise, swaps the right value with it's parent
        else {

            if(arr[right(index)] > arr[index]) {

                swap(right(index), index);
                trickleDown(right(index));
            }
        }
    }
}

// The root value is the largest in a
// max-heap, so this simply returns the
// value at index 0.
int Heap::largest() {
    return *arr;
}

// Destroys the array
Heap::~Heap() {
    delete arr;
}
