#pragma once

#include <unordered_map>
#include <list>

/*
 * 有序的HashMap
 * 插入O(1)，查找O(1)，可以按插入顺序for遍历
 */

template <typename Key, typename Value>
class OrderedHashMap
{
public: 
    void Add(const Key& key, const Value& value)
    {
        auto isExistItr = _map.find(key);
        if (isExistItr != _map.end())
        {
            _map[key] = value;
            _list.erase(key); // remove old key
            _list.push_back(key); // add at the tail of the list
        }
        else 
        {
            _map[key] = value;
            _list.push_back(key);
        }
    }

    void Add(const Key& key, Value&& value)
    {
        auto isExistItr = _map.find(key);
        if (isExistItr != _map.end())
        {
            _map[key] = std::move(value);
            _list.remove(key); // remove old key
            _list.push_back(key); // add at the tail of the list
        }
        else
        {
            _map[key] = std::move(value);
            _list.push_back(key);
        }
    }

    void Remove(const Key& key)
    {
        auto isExistItr = _map.find(key);
        if (isExistItr != _map.end())
        {
            _map.erase(isExistItr);
            _list.remove(key);
        }
    }

    bool Contains(const Key& key) const
    {
        return _map.contains(key);
    }

    const Value& operator[](const Key& key) const
    {
        auto itr = _map.find(key);
        return itr->second;
    }

    std::list<Key>::iterator begin()
    {
        return _list.begin();
    }

    std::list<Key>::const_iterator begin() const
    {
        return _list.begin();
    }

    std::list<Key>::iterator end()
    {
        return _list.end();
    }

    std::list<Key>::const_iterator end() const
    {
        return _list.end();
    }

private:
    std::unordered_map<Key, Value> _map;
    std::list<Key> _list;
};