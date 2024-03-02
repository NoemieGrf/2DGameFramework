#pragma once

#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "SFML/System/Vector2.hpp"

using uint = unsigned int;

template<typename Key, typename Value, typename Hash = std::hash<Key>>
using umap = std::unordered_map<Key, Value, Hash>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;

using vec2f = sf::Vector2f;
using vec2i = sf::Vector2i;
using vec2u = sf::Vector2u;

template<typename From, typename To>
sf::Vector2<To> VecConvert(const sf::Vector2<From>& src)
{
    sf::Vector2<To> result = sf::Vector2<To> {
        static_cast<To>(src.x),
        static_cast<To>(src.y)
    };

    return result;
}

template<typename T>
struct Vec2Hash
{
    size_t operator()(const sf::Vector2<T>& vec) const
    {
        return std::hash(vec.x) ^ std::hash(vec.y);
    }
};

using vec2fHash = Vec2Hash<float>;
using vec2iHash = Vec2Hash<int>;
using vec2uHash = Vec2Hash<unsigned int>;
