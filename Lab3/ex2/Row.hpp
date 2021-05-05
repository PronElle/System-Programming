//
// Created by elle on 22/04/21.
//

#ifndef EX2_ROW_HPP
#define EX2_ROW_HPP

#endif //EX2_ROW_HPP
#include <iostream>
#include <memory>

template<typename T>
class Row{
    std::unique_ptr<T[]> _ptr;

public:
    explicit Row(const unsigned int &n): _ptr(new T[n]) { };
    Row(): _ptr(nullptr) { };

    T & operator[](const unsigned int &index) const {
        return _ptr[index];
    }

    Row(const Row &val) = delete;

    Row(Row &&val) noexcept {
        _ptr.swap(val._ptr);
        val._ptr.reset();
    }

    Row& operator=(Row&& other) noexcept {
        _ptr.swap(other._ptr);
        other._ptr.reset();
        return *this;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream &out, const Row<T> &r) {
    out << r[0];
    return out;
}