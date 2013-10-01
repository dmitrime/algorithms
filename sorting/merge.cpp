#include <iostream>
using namespace std;

void merge(int ar[], int aux[], int lo, int mid, int hi) {
    for (int k = lo; k <= hi; k++)
        aux[k] = ar[k];

    int i = lo, j = mid+1;
    for (int k = lo; k <= hi; k++) {
        if      (i > mid)          ar[k] = aux[j++];
        else if (j > hi)           ar[k] = aux[i++];
        else if (aux[i] <= aux[j]) ar[k] = aux[i++];
        else                       ar[k] = aux[j++];
    }
}

void sort(int ar[], int aux[], int lo, int hi) {
    // TODO: hi <= lo means only 1 element or less, so return
    if (hi <= lo)
        return;
    int mid = lo + (hi-lo) / 2;
    sort(ar, aux, lo, mid);
    sort(ar, aux, mid+1, hi);
    merge(ar, aux, lo, mid, hi);
}

void iterative_sort(int ar[], int aux[], int lo, int hi) {
    for (int sz = 1; sz <= hi; sz = sz+sz) {
        for (int j = 0; j <= hi-sz; j += sz+sz) {
            merge(ar, aux, j, j+sz-1, min(j+sz+sz-1, hi));
        }
    }
}

void merge_sort(int ar[], int N) {
    int aux[N];
    iterative_sort(ar, aux, 0, N-1);
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 9, 2};
    int N = sizeof ar / sizeof ar[0];
    merge_sort(ar, N);
    for (int i = 0; i < N; i++)
        cout << ar[i] << " ";
    cout << endl;
    return 0;
}

