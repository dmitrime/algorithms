#include <iostream>
using namespace std;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void shell_sort(int ar[], int N) {
    int h = 1;
    while (h < N/3) 
        h = h*3 + 1;

    while (h >= 1)
    {
        cout << "h = " << h << endl;
        for (int i = h; i < N; i++)
        {
            int j = i-h;
            while (j >= 0 && ar[j+h] < ar[j])
            {
                swap(ar[j+h], ar[j]);
                j -= h;
            }
        }
        h /= 3;
    }
}

int main()
{
    int ar[] = {4, 5, 6, 1, 3, 0, 9, 2};
    int N = sizeof ar / sizeof ar[0];
    shell_sort(ar, N);
    for (int i = 0; i < N; i++)
        cout << ar[i] << " ";
    cout << endl;
    return 0;
}

