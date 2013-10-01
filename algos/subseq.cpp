#include <iostream>
#include <algorithm>
using namespace std;

int subseq_sum_v1(int ar[], int N) {
    int sum_max = 0, sum_sofar = 0;
    for (int i = 0; i < N; i++) {
        sum_sofar = max(sum_sofar + ar[i], 0);
        sum_max = max(sum_max, sum_sofar);
    }
    return sum_max;
}

int subseq_rec(int ar[], int lo, int hi) {
    if (lo > hi)
        return 0;
    if (lo == hi)
        return ar[lo];

    int mid = lo + (hi-lo) / 2;
    int left = 0, right = 0, sum = 0;
    for (int i = mid; i >= lo; i--) {
        sum += ar[i];
        left = max(sum, left);
    }
    sum = 0;
    for (int i = mid+1; i <= hi; i++) {
        sum += ar[i];
        right = max(sum, right);
    }

    int cross_sum = left + right;
    int left_best = subseq_rec(ar, lo, mid);
    int right_best = subseq_rec(ar, mid+1, hi);
    int result = max(cross_sum, max(left_best, right_best));

    return result;
}

int subseq_sum_v2(int ar[], int N) {
    return subseq_rec(ar, 0, N-1);
}

int main() {
    int ar[] = {1, 0, -2, -3, 3, 4, 5, -5, -1, 9};
    cout << subseq_sum_v2(ar, 10) << endl;
    return 0;
}
