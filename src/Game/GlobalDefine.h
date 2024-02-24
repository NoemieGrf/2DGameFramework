#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "SFML/System/Vector2.hpp"

using uint = unsigned int;

template<typename T, typename Y>
using umap = std::unordered_map<T, Y>;

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
