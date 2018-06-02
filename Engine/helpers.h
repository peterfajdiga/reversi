#pragma once

#include <vector>
#include <algorithm>


namespace helpers {

    template <class T>
    bool contains(const std::vector<T>& vector, const T& item) {
        return std::find(vector.begin(), vector.end(), item) != vector.end();
    }

    template <class T>
    T& getRandom(std::vector<T>& vector) {
        const size_t index = rand() % vector.size();
        return vector[index];
    }

    template <class T>
    const T& getRandom(const std::vector<T>& vector) {
        const size_t index = rand() % vector.size();
        return vector[index];
    }

}
