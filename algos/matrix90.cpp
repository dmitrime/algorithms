#include <iostream>
using namespace std;
//const int N = 3;
//const int M = 4;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

template<int M, int N> 
void matrix_zero(int mat[M][N])
{
    bool rows[M] = {false};
    bool cols[M] = {false};

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] == 0) {
                rows[i] = true;
                cols[j] = true;
            }

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            if (rows[i] || cols[j])
                mat[i][j] = 0;
}


template<int M, int N>
void rotate90_inplace(int mat[M][N])
{
    // swap the rows for right rotation, columns for left rotation
    for (int i = 0; i < N/2; i++)
        for (int j = 0; j < N; j++)
            swap(&mat[i][j], &mat[N-1-i][j]);

    // swap elements of symmetric diagonals (skip the main diagonal)
    for (int i = 1; i < N; i++)
        for (int j = 0; j < N-i; j++)
            swap(&mat[i+j][j], &mat[j][i+j]);
}



template<int M, int N>
void rotate90(int mat[M][N], int m2[M][N])
{
    for (int i = 0; i < N; i++)
        for (int j = N-1; j >= 0; j--)
            m2[i][N-1-j] = mat[j][i];
}


int main()
{
    const int M = 3, N = 3;
    //int mat[M][N] = {{1, 2, 3}, {4, 0, 6}, {7, 8, 9}, {1, 1, 1}};
    int mat[M][N] = {{1, 2, 3}, {4, 0, 6}, {7, 8, 9}};
    int mat2[M][N];
    cout << "Original" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    //rotate90(mat, mat2);
    rotate90_inplace<M,N>(mat);
    //matrix_zero<M,N>(mat);
    cout << "Rotated" << endl;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    return 0;
}

