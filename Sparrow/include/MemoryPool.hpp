#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP
#include <cstring>
class MemoryPool
{
public:
    MemoryPool(size_t c, bool inc_ = false);
    ~MemoryPool();
    void *malloc(size_t size);
    void destroyPool();
    bool hasEnoughSpace(size_t size);
    bool expandPool();

private:
    size_t capacity;
    void *pool = nullptr;
    void *p = nullptr;
    bool inc = false;
};

MemoryPool::MemoryPool(size_t c, bool inc_)
{
    capacity = c;
    inc = inc_;
    pool = ::operator new(capacity);
    p = pool;
}

void *MemoryPool::malloc(size_t size)
{
    if (hasEnoughSpace(size))
    {
        void *temp = p;
        p = (int *)p + size;
        return temp;
    }
    else if (inc)
    {
        if (expandPool)
            return malloc(size);
    }
    return nullptr;
}

bool MemoryPool::hasEnoughSpace(size_t size)
{
    if ((int *)pool + capacity - (int *)p >= size)
    {
        return true;
    }
    return false;
}

bool MemoryPool::expandPool()
{
    static int i = 1;
    i = i * 2;
    size_t new_capacity = capacity * i;
    void *new_pool = ::operator new(new_capacity);
    if (new_pool == nullptr)
    {
        return false;
    }
    else
    {
        std::memcpy(new_pool, pool, capacity);
        capacity = new_capacity;
        p = (int *)p - (int *)pool + (int *)new_pool;
        void *temp = pool;
        pool = new_pool;
        delete pool;
        return true;
    }
}
#endif
