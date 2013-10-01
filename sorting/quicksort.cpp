#include <iostream>
#include <algorithm>
using namespace std;

int partition(int ar[], int lo, int hi) {
    int v = ar[lo];
    int i = lo, j = hi+1;
    while (true) {
        while (ar[++i] < v) 
            if (i == hi) break; //TODO: == not >
        while (ar[--j] > v)
            if (j == lo) break; //TODO: == not <
        if (i >= j)
            break;
        swap(ar[i], ar[j]);
    }
    swap(ar[lo], ar[j]);
    return j;
}

void sort(int ar[], int lo, int hi) {
    if (hi <= lo)
        return;
    int mid = partition(ar, lo, hi);
    sort(ar, lo, mid-1);
    sort(ar, mid+1, hi);
}

void quick_sort(int ar[], int N) {
    random_shuffle(ar, ar+N);
    sort(ar, 0, N-1);
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 9, 2};
    int N = sizeof ar / sizeof ar[0];
    quick_sort(ar, N);
    for (int i = 0; i < N; i++)
        cout << ar[i] << " ";
    cout << endl;
    return 0;
}

