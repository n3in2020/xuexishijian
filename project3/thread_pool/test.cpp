#include <iostream>
#include <thread>
#include "thread_pool.h"
#include <chrono>
#include <fstream>

int main()
{   // 测试的任务是创建文件并输出“hello world”， 观察执行时间
    const unsigned long CNT = 10000;
    {
        std::cout << "[Thread pool]" << std::endl;
        ThreadPool tp;
        std::cout << "[start]" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        {
            for (int i = 0; i < CNT; ++i)
            {
                tp.submit(
                    [&i] {
                        std::ofstream ofs;
                        char buffer[1024];
                        sprintf(buffer, "./test/tp_file_%d", i);
                        ofs.open(buffer);
                        if (!ofs.is_open())
                        {
                            char error[1024];
                            sprintf(error, "Cannot open file %s", buffer);
                            perror(error);
                            ofs.close();
                            std::terminate();
                        }
                        ofs << "hello world" << std::endl;
                        ofs.close();
                    });
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "[end]" << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "duration:" << duration.count() << "ms" << std::endl;
    }
    std::cout << std::endl;
    {
        std::cout << "[single thread]" << std::endl;
        ThreadPool tp;
        std::cout << "[start]" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        {
            for (int i = 0; i < CNT; ++i)
            {
                std::ofstream ofs;
                char buffer[1024];
                sprintf(buffer, "./test/st_file_%d", i);
                ofs.open(buffer);
                if (!ofs.is_open())
                {
                    char error[1024];
                    sprintf(error, "Cannot open file %s", buffer);
                    perror(error);
                    ofs.close();
                    std::terminate();
                }
                ofs << "hello world" << std::endl;
                ofs.close();
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "[end]" << std::endl;
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "duration:" << duration.count() << "ms" << std::endl;
    }
    return 0;
}