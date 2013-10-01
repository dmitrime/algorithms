#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int partition(int ar[], int lo, int hi) {
    int v = ar[lo];
    int i = lo, j = hi+1;
    while (true) {
        while (ar[++i] < v) 
            if (i == hi) break;
        while (ar[--j] > v)
            if (j == lo) break;
        if (i >= j)
            break;
        swap(ar[i], ar[j]);
    }
    swap(ar[lo], ar[j]);
    return j;
}

void shuffle(int ar[], int N) {
    for (int i = 1; i < N; i++) {
        int r = rand() % (i+1);
        swap(ar[i], ar[r]);
    }
}

int kth_element(int ar[], int N, int k) {
    shuffle(ar, N);

    int lo = 0, hi = N-1;
    while (lo < hi) {
        int mid = partition(ar, lo, hi);
        if (mid == k)
            return ar[k];
        else if (mid > k) // TODO: Mistake here! Mixed up hi and lo updates!
            hi = mid-1;
        else if (mid < k)
            lo = mid+1;
    }
    return ar[k];
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 7, 2};
    int N = sizeof ar / sizeof ar[0];
    int k = 3;
    cout << kth_element(ar, N, k) << endl;
    return 0;
}

