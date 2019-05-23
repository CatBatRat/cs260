#include <iostream>
#include <stdlib.h>
#include <memory.h>
#include "Heap.h"

Heap::Heap(int newSize) {
    arr = (newSize <= 0) ? new int[16] : new int[newSize];
    size = (newSize <= 0) ? 16 : newSize;

    count = 0;
}

Heap::Heap(int *theArray, int arraySize) {
    arr = theArray;
    size = arraySize;
}

int Heap::left(int index) { return (2 * index) + 1; }

int Heap::right(int index) { return (2 * index) + 2; }

int Heap::parent(int index) { return (index - 1) / 2; }

int Heap::remove() {

    if(count <= 0)
        throw std::length_error("The heap is empty!");

    int value = *arr;

    count--;

    arr[0] = arr[count];

    trickleDown(0);

    return value;
}

void Heap::resize() {

    int newSize = 2 * size;

    int *newArr = new int[newSize];

    memcpy(newArr, arr, sizeof(int) * newSize);

    delete arr;

    arr = newArr;
    size = newSize;
}

void Heap::insert(int value) {

    if(count >= size)
        resize();

    arr[count] = value;

    bubbleUp(count);

    count++;
}

void Heap::bubbleUp(int index) {

    if(index == 0)
        return;

    if(arr[parent(index)] < arr[index]) {

        swap(parent(index), index);

        bubbleUp(parent(index));
    }

    else
        return;
}

void Heap::swap(int indexOne, int indexTwo) {

    int value = arr[indexOne];

    arr[indexOne] = arr[indexTwo];
    arr[indexTwo] = value;
}

void Heap::trickleDown(int index) {

    if(left(index) >= count)
        return;

    if(right(index) >= count) {

        if(arr[left(index)] < arr[index]) {

            swap(left(index), index);
            trickleDown(left(index));
        }

    }
    else {

        if(arr[left(index)] < arr[right(index)]) {

            if(arr[left(index)] < arr[index]) {

                swap(left(index), index);
                trickleDown(left(index));
            }

            trickleDown(left(index));
        }

        else {

            if(arr[right(index)] < arr[index]) {

                swap(right(index), index);
                trickleDown(right(index));
            }
        }
    }
}

int Heap::largest() {
    return *arr;
}

Heap::~Heap() {
    delete arr;
}
