#pragma once

#include <vector>
#include <algorithm>


namespace helpers {

    template <class T>
    bool contains(const std::vector<T>& vector, const T& item) {
        return std::find(vector.begin(), vector.end(), item) != vector.end();
    }

}
