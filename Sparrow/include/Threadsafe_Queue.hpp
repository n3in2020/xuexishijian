#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "Threadsafe_Queue.hpp"

template <typename T>
class TSQueue
{
public:
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(mutex);
        q.push(std::move(value));
        cv.notify_one();
    }

    void wait_and_pop(T &value)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this] { return !q.empty(); });
        value = std::move(q.front());
        q.pop();
    }

    bool try_pop(T &value)
    {
        std::lock_guard<std::mutex> lock(mutex);
        if (q.empty())
            return false;
        else
        {
            value = std::move(q.front());
            q.pop();
            return true;
        }
    }

private:
    std::mutex mutex;
    std::queue<T> q;
    std::condition_variable cv;
};
#endif