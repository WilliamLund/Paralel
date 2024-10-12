#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <cmath>
#include <atomic>
#include <omp.h>

int main(int argc, char *argv[])
{
    int const n = 2000;

    int b[n];
    int **A = new int*[n];
    int count = 1;
    for(int i = 0; i < n; i++){
        b[i]=count;
        for(int j = 0; j < n; j++){
            if (j >= i) {
                A[i][j] = count;
                count++;
            }else{
                A[i][j] = 0;
            }
        }
    }

    int x[n];
    for (int row = 0; row < n; row++)
        x[row] = b[row];
    for (int col = n - 1; col >= 0; col--)
    {
        x[col] /= A[col][col];
        for (int row = 0; row < col; row++)
            x[row] -= A[row][col] * x[col];
    }
    /*
    for(int i = 0; i < n; i++){
        std::cout<< x[i] <<" ";
    }*/
}
