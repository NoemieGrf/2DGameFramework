#pragma once

#include <unordered_map>
#include <unordered_set>
#include <memory>

using uint = unsigned int;

template<typename T, typename Y>
using umap = std::unordered_map<T, Y>;

template<typename T>
using uset = std::unordered_set<T>;

template<typename T>
using uptr = std::unique_ptr<T>;

template<typename T>
using sptr = std::shared_ptr<T>;
