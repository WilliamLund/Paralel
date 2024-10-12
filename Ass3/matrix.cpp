#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <cmath>
#include <atomic>
#include <omp.h>

#define dim 200
void usage(char *program)
{
    std::cout << "Usage: " << program << " C N" << std::endl;
    std::cout << std::endl;
    std::cout << "  C: number of Cores" << std::endl;
    std::cout << "  N: number" << std::endl;
    exit(1);
}

void matrix_mult(int a[][dim], int b[][dim], int c[][dim],int cores)
{
#pragma omp parallel default(shared) shared(a, b, c) num_threads(cores)
#pragma omp for schedule(static) collapse(2)

    for (int i = 0; i < dim; i++)
    {
       
        for (int j = 0; j < dim; j++)
        {
             
            for (int k = 0; k < dim; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int cores;
    try
    {
        cores = std::stoi(argv[1]);
    }
    catch (std::exception const &)
    {
        usage(argv[0]);
    }
    
    auto start_time = std::chrono::system_clock::now();
    for (int i = 0; i < 300; i++){
    int arr1[dim][dim];
    int arr2[dim][dim];
    int arr3[dim][dim];

    int count = 0;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if(count>10)
            {
                count=0;
            }
            arr1[i][j] = ++count;
            arr2[j][i] = ++count;
            arr3[i][j] = 0;
        }   
    }

    matrix_mult(arr1,arr2,arr3,cores);
    }
    std::chrono::duration<double> duration = (std::chrono::system_clock::now() - start_time);
    std::cout << "Finished in " << duration.count() << " seconds (wall clock)." << std::endl;
    /*for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            std::cout<<arr3[i][j]<<" ";
        }
        std::cout<<""<<std::endl;    
    }*/
}

