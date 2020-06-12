#ifndef LRUCACHE_H
#define LRUCACHE_H
#include <list>
#include <unordered_map>
#include <iterator>
#include <memory>

template <typename key, typename value>
class LRUCache
{
public:
    LRUCache(int c) : capacity(c), list{}, map{} {}

    typedef typename std::pair<key, value> key_value_pair;

    void put(key k, value v);
    std::unique_ptr<value> get(key k);
private:
    int capacity;
    std::list<key_value_pair> list;
    std::unordered_map<key, decltype(list.begin())> map;
};

template <typename key, typename value>
void LRUCache<key, value>::put(key k, value v)
{
    if (map.find(k) != map.end())
    {
        auto it = map[k];
        list.erase(it);
        map.erase((*it).first);
    }
    if (list.size() == capacity)
    {
        auto it = list.end();
        it--;
        map.erase((*it).first);
        list.pop_back();
    }
    list.push_front(key_value_pair(k, v));
    map[k] = list.begin();
}

template <typename key, typename value>
std::unique_ptr<value> LRUCache<key, value>::get(key k)
{
    std::unique_ptr<value> ret;
    if (map.find(k) != map.end())
    {
        auto it = map[k];
        ret = std::make_unique<value>((*it).second);
        list.erase(it);
        list.push_front(key_value_pair(k, *ret));
        map[k] = list.begin();
    }
    return ret;
}

#endif
