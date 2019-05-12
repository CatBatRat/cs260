#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

const int HEAP_SIZE = 100000000;

using namespace std;

inline int left(int index);
inline int right(int index);
inline int parent(int index);
inline void intSwap(int &left, int &right);
void bubbleUp(int arr[], int index);
void trickleDown(int arr[], int index, int size);
void add(int arr[], int index, int &size);
int remove(int arr[], int &size);

int main() {

  int size = 0;
  std::srand(static_cast<int>(time(nullptr)));

  int *heap = new int[HEAP_SIZE];

  for (int r = 0; r < HEAP_SIZE; r++) {
    int randn = rand() % 99 + 1;
    add(heap, randn, size);
  }

  int end = size;
  cout << "Built Heap!" << endl;
  for(int i = 0; i < HEAP_SIZE; i++)
    heap[end--] = remove(heap, size);
  cout << "Sorted Heap" << endl;
  for(int i = HEAP_SIZE-1; i >= 0; i--)
    cout << heap[i] << " ";
  cout << endl;

  delete[] heap;
  return 0;
}
inline void intSwap(int &l, int &r) {
  l ^= r;
  r ^= l;
  l ^= r;
}

inline int left(int i) { return 2 * i + 1; }

inline int right(int i) { return 2 * i + 2; }

inline int parent(int i) { return (i - 1) / 2; }

void bubbleUp(int arr[], int i) {
  int p = parent(i);
  while (i > 0 && (arr[i] > arr[p])) {
    intSwap(arr[p], arr[i]);
    i = p;
    p = parent(i);
  }
}

void add(int arr[], int n, int &s) {
  arr[s] = n;
  bubbleUp(arr, s);
  s++;
}


int remove(int arr[], int &size) {
  int temp = arr[0];
  arr[0] = arr[size - 1];
  trickleDown(arr, 0, --size);
  return temp;
}

void trickleDown(int arr[], int i, int size) {
  do {
    int j = -1;
    int r = right(i);
    if (r < size && arr[r] > arr[i]) {
      int l = left(i);
      if (arr[l] > arr[r]) {
        j = l;
      } else {
        j = r;
      }
    } else {
      int l = left(i);
      if (l < size && arr[l] > arr[i]) {
        j = l;
      }
    }
    if (j >= 0)
      intSwap(arr[i], arr[j]);
    i = j;
  } while (i >= 0);
}
