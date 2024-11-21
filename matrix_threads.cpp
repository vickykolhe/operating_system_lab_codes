#include <bits/stdc++.h>
using namespace std;

const int SIZE = 3;
int a[SIZE][SIZE];
int b[SIZE][SIZE];
int c[SIZE][SIZE];

struct Matrixposition
{
    int row;
    int col;
};

void *matrixadd(void *arg)
{
    Matrixposition *pos = (Matrixposition *)arg;
    int row = pos->row;
    int col = pos->col;

    c[row][col] = a[row][col] + b[row][col];
    pthread_exit(0);
}
void *matrixmul(void *arg)
{
    Matrixposition *pos = (Matrixposition *)arg;
    int row = pos->row;
    int col = pos->col;

    c[row][col] = 0;
    for (int k = 0; k < SIZE; k++)
    {
        c[row][col] += a[row][k] * b[k][col];
    }
    pthread_exit(0);
}

void display(int mat[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << "a[" << i << "][" << j << "]: ";
            cin >> a[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << "b[" << i << "][" << j << "]: ";
            cin >> b[i][j];
        }
    }

    pthread_t thread[SIZE][SIZE];
    Matrixposition pos[SIZE][SIZE];

    // matrix addition

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            pos[i][j] = {i, j};
            pthread_create(&thread[i][j], nullptr, matrixadd, (void *)&pos[i][j]);
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            pthread_join(thread[i][j], nullptr);
        }
    }
    display(c);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            pos[i][j] = {i, j};
            pthread_create(&thread[i][j], nullptr, matrixmul, (void *)&pos[i][j]);
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            pthread_join(thread[i][j], nullptr);
        }
    }
    display(c);
}