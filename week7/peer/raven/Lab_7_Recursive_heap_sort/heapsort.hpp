#include <iostream>
using namespace std;
void heapSort(int* arr, const int SIZE)
{
    int* tempArr = new int[SIZE];
    int newIndex = -1;
    for (int i = 0; i < SIZE; i++)
    {
        newIndex++;
        tempArr[newIndex] = arr[i];
        int temp = newIndex;

        while(tempArr[temp/2] < tempArr[temp])
        {
            int holder = tempArr[temp/2];
            tempArr[temp/2] = tempArr[temp];
            tempArr[temp] = holder;
            temp = temp/2;
        }
    }

    for(int i = 0; i < SIZE; i++)
        arr[i] = tempArr[i];

    delete [] tempArr;
}

