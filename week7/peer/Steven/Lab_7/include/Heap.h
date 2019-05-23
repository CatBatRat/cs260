#ifndef HEAP_H
#define HEAP_H


class Heap
{
    public:
        Heap(int size);
        Heap(int *theArray, int arraySize);
        int left(int index);
        int right(int index);
        int parent(int index);
        void resize();
        void insert(int value);
        void bubbleUp(int index);
        void trickleDown(int index);
        void swap(int indexOne, int indexTwo);
        int remove();
        int largest();
        int getSize() { return size; }
        void setSize(int newSize) { size = newSize; }
        ~Heap();

    private:
        int *arr;
        int size;
        int count;
};

#endif
