#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void insertion_sort(int ar[], int N) {
    for (int i = 0; i < N; i++)
    {
        int j = i-1;
        while (j >= 0 && ar[j+1] < ar[j])
        {
            swap(ar[j+1], ar[j]);
            j--;
        }
    }
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 9, 2};
    int N = sizeof ar / sizeof ar[0];
    insertion_sort(ar, N);
    for (int i = 0; i < N; i++)
        cout << ar[i] << " ";
    cout << endl;
    return 0;
}

