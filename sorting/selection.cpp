#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void selection_sort(int ar[], int N) {
    for (int i = 0; i < N; i++)
    {
        int m = i;
        for (int j = i+1; j < N; j++)
            if (ar[m] > ar[j])
                m = j;
        cout << "swapping " << ar[i] << " and " << ar[m] << endl;
        swap(ar[i], ar[m]);
    }
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 9, 2};
    int N = sizeof ar / sizeof ar[0];
    selection_sort(ar, N);
    for (int i = 0; i < N; i++)
        cout << ar[i] << " ";
    cout << endl;
    return 0;
}

