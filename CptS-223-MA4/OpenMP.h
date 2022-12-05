// OpenMP header
// #include <omp.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

void hello_world() {
    printf("\nStart hello_world()\n");
    // Get the total number of cores in the system
    const auto processor_count = std::thread::hardware_concurrency();
    // Set the number of threads used in OpenMP
    omp_set_num_threads(processor_count);
    // Begin of parallel region
#pragma omp parallel
    {
        // Getting thread number
        int tid = omp_get_thread_num();
        printf("Welcome from thread = %d\n",
               tid);

        if (tid == 0) {

            // Only master thread does this
            int nthreads = omp_get_num_threads();
            printf("Number of threads = %d: this message from thread #%d\n",
                   nthreads, tid);
        }
    }
    printf("\nFinish hello_world()\n");
}

void cal_sum(){
    printf("\nStart cal_sum()\n");
    int sum = 0;
    int data_size = 100000000;
    int num_threads = 2;
    int workload = data_size/num_threads;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        data[i] = 1;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    omp_set_num_threads(num_threads);
#pragma omp parallel
    {
        // Getting thread number
        int tid = omp_get_thread_num();
        int local_sum = 0; // Use local sum instead of the global sum to avoid resource competition
        for (int i = tid*workload; i < (tid + 1)*workload; ++i) {
            local_sum += data[i];
        }
        sum += local_sum;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
    << "[microseconds]" << std::endl;
    assert(sum == data_size);
    printf("\nFinish cal_sum(): assert pass!\n");
}

// Find the max value in the data array
void cal_max() {
    printf("\nStart cal_max()\n");
    int max = 0;
    int data_size = 100000000;
    int num_threads = 2;
    int workload = data_size/num_threads;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i) {
        data[i] = rand() % data_size;
    }
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // OpenMP implementation: start your code here
    // You need to follow the example given in cal_sum() and store the max value in the "max" variable created above.
    // The max found by your OpenMap should be identical to the max found by stl
    int *max_list = new int[num_threads];

#pragma omp parallel
    {
        int tid = omp_get_thread_num();
        // split data and find max of each dataset
        for (int i = tid*workload; i < (tid + 1)*workload; ++i) {
            if (data[i] > max_list[tid]) {
                max_list[tid] = data[i];
            }
        }
    }

    // determine maximum of max_list
    for (int i = 0; i < num_threads; i++) {
        if (max_list[i] > max) {
            max = max_list[i];
        }
    }
    // OpenMP implementation: stop here
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << "[microseconds]" << std::endl;
    std::vector<int> vect(data, data + data_size);
    int max_found_by_stl = *std::max_element(vect.begin(), vect.end());
    std::cout << "max found by stl: " << max_found_by_stl << ", max found by OpenMP " << max << std::endl;
    printf("\nFinish cal_max()\n");
}