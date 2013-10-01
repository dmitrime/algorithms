#include <iostream>
using namespace std;

int binsearch_normal(int key, int ar[], int N) {
    int lo = 0, hi = N-1;

    while (lo <= hi) {
        int mid = lo + (hi-lo) / 2;
        if (ar[mid] > key) 
            hi = mid-1;
        else if (ar[mid] < key) 
            lo = mid+1;
        else return mid;
    }
    return -1;
}

int binsearch(int key, int ar[], int N) {
    int lo = 0, hi = N-1;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        if (ar[mid] == key)
            return mid;

        if (ar[mid] >= ar[lo]) {
            if (key >= ar[lo] && key < ar[mid])
                hi = mid-1;
            else
                lo = mid+1;
        }
        else {
            if (key > ar[mid] && key <= ar[hi])
                lo = mid+1;
            else
                hi = mid-1;
        }
    }
    return -1;
}

int binsearch(int key, int ar[], int lo, int hi) {
    int mid = lo + (hi-lo)/2;
    if (ar[mid] == key)
        return mid;
    if (lo >= hi)
        return -1;

    if (ar[mid] >= ar[lo]) {
        if (key >= ar[lo] && key < ar[mid])
            return binsearch(key, ar, lo, mid-1);
        else
            return binsearch(key, ar, mid+1, hi);
    }
    else {
        if (key > ar[mid] && key <= ar[hi])
            return  binsearch(key, ar, mid+1, hi);
        else
            return binsearch(key, ar, lo, mid-1);
    }
}

int main() {
    int ar[] = {3, 4, 5, 6, 7, 0, 1, 2};
    int N = sizeof ar / sizeof ar[0];
    for (int i = 0; i < N+2; i++)
        cout << "Searching for " << i << " " << binsearch(i, ar, N) << endl;

    int ar2[] = {3, 4, 5, 6, 7};
    N = sizeof ar2 / sizeof ar2[0];
    for (int i = 3; i < N+5; i++)
        cout << "Searching for " << i << " " << binsearch_normal(i, ar, N) << endl;
    return 0;
}
