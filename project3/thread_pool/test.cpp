#include "thread_pool.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <random>
#include <algorithm>
auto IO_bound_job(int N)
{
    ThreadPool tp(N);
    const unsigned jobs = 10000;
    std::atomic<int> n{0};
    system("rm -rf testdir");
    system("mkdir testdir");
    auto start = std::chrono::high_resolution_clock::now();
    {
        for (int i = 0; i < jobs; ++i)
        {
            tp.submit([&] {
                std::ofstream ofs;
                char buffer[1024];
                sprintf(buffer, "testdir/%d", ++n);
                ofs.open(buffer, std::ios_base::out | std::ios_base::trunc);
                if (ofs.is_open())
                {
                    for (int j = 0; j < 1000; ++j)
                    {
                        ofs << "hello world" << std::endl;
                    }
                    ofs.close();
                }
                else
                {
                    perror("when open file");
                }
            });
        }
        tp.waitFinished();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration;
}

void benchmark_IO_bound(int N)
{
    const int TEST_SIZE = 5;
    auto total = std::chrono::milliseconds(0);

    std::cout << "[IO bound benchmark]" << std::endl;
    std::cout << "[threads = " << N << "]" << std::endl;
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        std::cout << "[job " << i << " start]" << std::endl;
        auto duration = IO_bound_job(N);
        total += duration;
        std::cout << "[end]" << std::endl;
        std::cout << "[duration = " << duration.count() << "ms]" << std::endl;
    }
    auto avg = total / TEST_SIZE;
    std::cout << "\n\n[avg = " << avg.count() << "ms]" << std::endl;
}

auto CPU_bound_job(int N)
{
    ThreadPool tp(N);
    const unsigned jobs = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    {
        for (int i = 0; i < jobs; ++i)
        {
            tp.submit([&] {
                std::random_device rd;
                std::mt19937 mt(rd());
                std::vector<int> data(10000);
                std::generate_n(std::back_inserter(data), data.capacity(), [&] { return mt(); });
                std::sort(data.begin(), data.end());
            });
        }
        tp.waitFinished();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return duration;
}

void benchmark_CPU_bound(int N)
{
    const int TEST_SIZE = 5;
    auto total = std::chrono::milliseconds(0);
    std::cout << "[CPU bound benchmark]" << std::endl;
    std::cout << "[threads = " << N << "]" << std::endl;
    for (int i = 0; i < TEST_SIZE; ++i)
    {
        std::cout << "[job " << i << " start]" << std::endl;
        auto duration = CPU_bound_job(N);
        total += duration;
        std::cout << "[end]" << std::endl;
        std::cout << "[duration = " << duration.count() << "ms]" << std::endl;
    }
    auto avg = total / TEST_SIZE;
    std::cout << "\n\n[avg = " << avg.count() << "ms]" << std::endl;
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        // benchmark_IO_bound(atoi(argv[1]));
        benchmark_CPU_bound(atoi(argv[1]));
    }
    else
    {
        printf("usage: %s n\n", argv[0]);
    }
    return 0;
}