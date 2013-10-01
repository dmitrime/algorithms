#include <iostream>
using namespace std;

void merge(int ar1[], int n1, int ar2[], int n2) {
    int k = n1;
    for (int i = 0; i < n2; i++)
    {
        ar1[k++] = ar2[i];
        int j = k-2;
        while (j >= 0 && ar1[j+1] < ar1[j])
        {
            swap(ar1[j], ar1[j+1]);
            j--;
        }
    }
}

int main()
{
    int ar1[] = {2, 4, 6, 7, 8, 9, 0, 0, 0};
    int ar2[] = {1, 3, 5};

    merge(ar1, 6, ar2, 3);
    int N = sizeof ar1 / sizeof ar1[0];
    for (int i = 0; i < N; i++)
        cout << ar1[i] << " ";
    cout << endl;
    return 0;
}

