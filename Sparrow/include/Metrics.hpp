#ifndef METRICS_HPP
#define METRICS_HPP
#include <cstddef>
#include <chrono>
template <typename T>
class Counter
{
public:
    Counter() {}
    ~Counter() { ++count; }
    static size_t getCount() { return count; }

private:
    static size_t count;
};
template <typename T>
size_t Counter<T>::count = 0;

template <typename T>
class Timer
{
public:
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start);
    }
    static std::chrono::duration<double, std::milli> getDuration()
    {
        return duration;
    }

private:
    std::chrono::high_resolution_clock::time_point start;
    static std::chrono::duration<double, std::milli> duration;
};
template <typename T>
std::chrono::duration<double, std::milli> Timer<T>::duration = std::chrono::duration<double, std::milli>(0);
#endif