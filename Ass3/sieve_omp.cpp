#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <cmath>
#include <atomic>
#include <omp.h>


int *SoE(int list[], int max, int *primSize)
{
    int k = 2;
    int count = 1;
    int temp = 1;
    int primCount = 0;
    while (temp < max)
    {
        if (list[temp] != 0)
        {
            primCount++;
            k = list[temp];

            count = (k * k) - 1;

            while (count < max)
            {
                list[count] = 0;

                count += k;
            }
        }
        temp++;
    }
    int *prim = (int *)calloc(primCount, sizeof(int));

    count = 0;
    for (int i = 0; i < max; i++)
    {
        if (list[i] != 0)
        {
            prim[count] = list[i];
            count++;
        }
    }
    *primSize = count;
    return prim;
}

int *primCalc(int start,int max, int list[], int prim[], int primSize, std::atomic<int> *primTot)
{
    int numberOfNumbers=(max-start)/omp_get_num_threads();
    if(numberOfNumbers==0)
    {
        numberOfNumbers=1;
    }
    int begin = start + ((numberOfNumbers) *omp_get_thread_num() );
    int end = begin + numberOfNumbers-1;
    
    int count = begin - 1;
    int k = 0;

    for (int i = 0; i < primSize; i++)
    {
        while (count < end)
        {
            if (list[count] != 0 && list[count] % prim[i] == 0)
            {
                k = prim[i];
                while (count <= end)
                {
                    list[count] = 0;
                    count += k;
                }
            }
            count++;
        }
        count = begin - 1;
    }

    count = begin - 1;
    while (count < end)
    {
        if (list[count] != 0)
        {
            (*primTot)++;
        }
        count++;
    }

    // int *prims = (int *)calloc(primCount, sizeof(int));
    return 0;
}

void usage(char *program)
{
    std::cout << "Usage: " << program << " C N" << std::endl;
    std::cout << std::endl;
    std::cout << "  C: number of Cores" << std::endl;
    std::cout << "  N: number" << std::endl;
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        usage(argv[0]);
    }

    // threads = argv[1]
    int cores;
    try
    {
        cores = std::stoi(argv[1]);
    }
    catch (std::exception const &)
    {
        usage(argv[0]);
    }
    if (cores < 1)
    {
        usage(argv[0]);
    }

    // size = argv[2]
    int num;
    try
    {
        num = std::stoi(argv[2]);
    }
    catch (std::exception const &)
    {
        usage(argv[0]);
    }
    if (num < 1)
    {
        usage(argv[0]);
    }
    /*
        auto start_time = std::chrono::system_clock::now();
        std::thread *t = new std::thread[threads];

        for (int i = 0; i < threads; i++)
        {
            t[i] = std::thread(balance, i, trapezes, threads, result);
        }

        for (int i = 0; i < threads; i++)
        {
            t[i].join();
        }

        std::chrono::duration<double> duration =
            (std::chrono::system_clock::now() - start_time);
        // *** timing ends here ***

        std::cout << "Finished in " << duration.count() << " seconds (wall clock)." << std::endl;
        */

    int *arr = (int *)calloc(num, sizeof(int));
    for (int i = 1; i < num; i++)
    {
        arr[i] = i + 1;
    }

    int sqrtNum = (int)sqrt(num);
    std::atomic<int> primTot{};
    int *primCount = (int *)calloc(1, sizeof(int));
    int *prim = SoE(arr, sqrtNum, primCount);
    primTot+=(*primCount);

    auto start_time = std::chrono::system_clock::now();

    int start = sqrtNum + 1;


    #pragma omp parallel num_threads(cores)

    primCalc(start,num,arr,prim,*primCount,&primTot);

   
    std::chrono::duration<double> duration =
        (std::chrono::system_clock::now() - start_time);
    
    #pragma omp barrier
    int *primNum = (int *)calloc(primTot+1, sizeof(int));
    int count=0;
    for (int i = 0; i < num; i++)
    {
        if(arr[i]!=0)
        {
            primNum[count]=arr[i];
            count++;
        }
    }
    /*
    for(int i =0;i<primTot;i++)
    {
        std::cout<<"Prim: "<< primNum[i]<<std::endl;
    }*/
    std::cout << primTot << std::endl;

    std::cout << "Finished in " << duration.count() << " seconds (wall clock)." << std::endl;
    //delete (primNum);
    //delete (arr);
    //delete (primCount);


    return 0;
}