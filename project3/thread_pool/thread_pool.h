#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <vector>
#include <atomic>
#include <future>
#include <memory>
class ThreadPool
{
public:
    ThreadPool(int N = std::thread::hardware_concurrency()) : done{false}, busy(0)
    {
        // 创建线程并令其执行work函数
        for (unsigned i = 0; i < N; ++i)
        {
            threads.push_back(std::thread(&ThreadPool::work, this));
        }
    }

    ~ThreadPool()
    {
        // 线程池工作完成并通知所有线程
        done = true;
        cv.notify_all();
        // 等待线程结束
        for (int i = 0; i < threads.size(); ++i)
        {
            if (threads[i].joinable())
                threads[i].join();
        }
    }

    // // 提交任务
    // template <typename Func, typename... Args>
    // std::future<std::result_of_t<Func(Args...)>> submit(Func &&func, Args &&... args)
    // {
    //     using RetType = std::result_of_t<Func(Args...)>;
    //     auto task = std::make_shared<std::packaged_task<RetType()>>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    //     auto res = task->get_future();
    //     {
    //         // 将新任务加入队列中
    //         std::lock_guard<std::mutex> lock(m);
    //         if(done.load())
    //             throw std::runtime_error("The thread pool is done");
    //         tasks.push([task]{(*task)();});
    //     }
    //     // 通知一个线程有新任务加入
    //     cv.notify_one();
    //     return res;
    // }
    template <typename Func, typename... Args>
    void submit(Func &&func, Args &&... args)
    {
        std::lock_guard<std::mutex> lock(m);
        tasks.push(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        cv.notify_one();
    }

    void waitFinished()
    {
        std::unique_lock<std::mutex> lock(m);
        cv_finished.wait(lock, [this] { return tasks.empty() && (busy == 0); });
    }

private:
    std::atomic<bool> done;
    mutable std::mutex m;
    std::condition_variable cv;
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;
    std::atomic<unsigned> busy;
    std::condition_variable cv_finished;
    // 线程工作
    void work()
    {
        std::function<void()> task;
        while (true)
        {
            // 获取队列中的任务
            {
                std::unique_lock<std::mutex> lock(m);
                // 等待队列中的新任务或者线程池工作完成
                cv.wait(lock, [this] { return !tasks.empty() || done.load(); });
                // 如果线程池工作完成，结束线程工作
                if (done.load())
                {
                    return;
                }
                else
                {
                    // 获取队列中的新任务
                    ++busy;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
            }

            // 执行任务
            task();
            --busy;
            cv_finished.notify_all();
        }
    }
};
#endif