#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
inline void remove(std::vector<T*>& v, const T &item)
{
    v.erase(std::remove(v.begin(), v.end(), item), v.end());
}
