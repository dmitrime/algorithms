#include <iostream>
using namespace std;

class Heap
{
    private:
        int *heap;
        int size;

        void push_up(int n);

        void push_down(int n);

    public:
        Heap(int n) {
            heap = new int[n+1];
            size = 0;
        }
        ~Heap() {
            delete[] heap;
        }

        void insert(int key);

        int pop_max();

        inline int max() {
            if (size > 0)
                return heap[1];
            return 0;
        }
        inline bool is_empty() {
            return size == 0;
        }
        inline int length() {
            return size;
        }
};

void Heap::push_up(int k) {
    while (k > 1 && heap[k] > heap[k/2]) {
        swap(heap[k], heap[k/2]);
        k /= 2;
    }
}

void Heap::push_down(int k) {
    while (2*k <= size) {
        int j = 2*k;
        if (j < size && heap[j] < heap[j+1])
            j++;

        if (heap[k] < heap[j]) {
            swap(heap[k], heap[j]);
            k = j;
        }
        else 
            break;
    }
}

int Heap::pop_max() {
    int mx = heap[1];
    swap(heap[1], heap[size]);
    heap[size--] = 0;
    push_down(1);
    return mx;
}

void Heap::insert(int key) {
    heap[++size] = key;
    push_up(size);
}

int main()
{
    Heap heap(10);
    heap.insert(10);
    heap.insert(2);
    heap.insert(5);
    heap.insert(3);
    heap.insert(4);
    heap.insert(11);

    cout << "size = " << heap.length() << endl;
    cout << heap.pop_max() << endl;
    cout << heap.pop_max() << endl;
    cout << heap.pop_max() << endl;
    cout << heap.pop_max() << endl;
    cout << heap.pop_max() << endl;
    return 0;
}

