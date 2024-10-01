#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <stdexcept>

template <typename T, size_t S = 2>
class Vector
{
private:
    std::size_t size;
    std::size_t capacity;
    std::unique_ptr<T[]> data;

    void resize(std::size_t newCapacity);
    void reserve(std::size_t reserveCapacity);

    // copy constructor
    Vector(const Vector& obj);

    // copy assignment operator
    Vector& operator=(const Vector& obj);

    // move constructor
    Vector(Vector&& obj) noexcept;

    // move assignment operator
    Vector& operator=(Vector&& obj) noexcept;

public:
    // Default constructor
    Vector();
    // Destructor
    virtual ~Vector();

    void push(const T& val);
    void push(T&& val);
    void pop();
    void clear();
    void shrink_to_fit();
    inline std::size_t size() const;
    inline std::size_t capacity() const;
    bool empty() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
};

#include "vector.ipp"