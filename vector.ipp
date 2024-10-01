#include "vector.hpp"

// Default constructor
template <typename T, size_t S>
Vector<T, S>::Vector() : size(0), capacity(S), data(std::make_unique<T[]>(S)) 
{
    std::cout << "Default constructor called" << std::endl;
}

// Destructor
template <typename T, size_t S>
Vector<T, S>::~Vector() 
{
    // No need to manually do resource management since we use RAII with smart pointers
    std::cout << "Destructor called" << std::endl;
}

// Copy constructor
template <typename T, size_t S>
Vector<T, S>::Vector(const Vector& obj) : size(obj.size), capacity(obj.capacity) 
{
    if(obj.data)
    {
        data = std::make_unique<T[]>(obj.capacity);
        std::copy(obj.data.get(), obj.data.get() + obj.size, data.get());
    }
}

// Copy assignment operator
template <typename T, size_t S>
Vector<T, S>& Vector<T, S>::operator=(const Vector& obj) 
{
    if(this != &obj)
    {
        size = obj.size;
        capacity = obj.capacity;

        if(obj.data)
        {
            data = std::make_unique<T[]>(obj.capacity);
            std::copy(obj.data.get(), obj.data.get() + obj.size, data.get());
        }
    }
    return *this;
}

// Move constructor
template <typename T, size_t S>
Vector<T, S>::Vector(Vector&& obj) noexcept : size(obj.size), capacity(obj.capacity), data(std::move(obj.data))
{
    obj.size = 0;
    obj.capacity = 0;
}

// Move assignment operator
template <typename T, size_t S>
Vector<T, S>& Vector<T, S>::operator=(Vector&& obj) noexcept
{
    if(this != &obj)
    {
        size = obj.size;
        capacity = obj.capacity;
        data = std::move(obj.data);

        obj.size = 0;
        obj.capacity = 0;
    }
    return *this;
}

template <typename T, size_t S>
void Vector<T, S>::resize(std::size_t newCapacity)
{
    if (newCapacity > capacity)
    {
        std::unique_ptr<T[]> newData = std::make_unique<T[]>(newCapacity);
        for (std::size_t i = 0; i < size; ++i)
        {
            newData[i] = std::move(data[i]);
        }
        data = std::move(newData);
        capacity = newCapacity;
    }
}

template <typename T, size_t S>
void Vector<T, S>::reserve(std::size_t reserveCapacity)
{
    if (reserveCapacity > this->capacity) resize(reserveCapacity);
}

template <typename T, size_t S>
void Vector<T, S>::shrink_to_fit()
{
    if (capacity > size)
    {
        resize(size);
    }
}

template <typename T, size_t S>
void Vector<T, S>::push(const T& val)
{
    if(capacity == size)
    {
        resize(capacity * 2);
    }

    data[size++] = val;
}

template <typename T, size_t S>
void Vector<T, S>::push(T&& value) 
{
    if (capacity == 0) {
        resize(1);
    } else if (capacity == size) {
        resize(capacity * 2);
    }
    data[size++] = std::move(value); // Move the value
}

template <typename T, size_t S>
void Vector<T, S>::pop()
{
    if(size > 0)
    {
        --size;
        // No need to manually call the destructor because we use smart pointers
    } 
    else
    {
        throw std::out_of_range("Cannot pop_back from an empty vector");
    }
}

template <typename T, size_t S>
void Vector<T, S>::clear()
{
    size = 0;
    // No need to manually call the destructor because we use smart pointers
}

template <typename T, size_t S>
inline std::size_t Vector<T, S>::size() const
{
    return this->size;
}

template <typename T, size_t S>
inline std::size_t Vector<T, S>::capacity() const
{
    return this->capacity;
}

template <typename T, size_t S>
inline bool Vector<T, S>::empty() const
{
    return size == 0;
}

template <typename T, size_t S>
T& Vector<T, S>::operator[](std::size_t index)
{
    if(index >= size) throw std::out_of_range("Out of range");

    return data[index];
}

template <typename T, size_t S>
const T& Vector<T, S>::operator[](std::size_t index) const
{
    if(index >= size) throw std::out_of_range("Out of range");

    return data[index];
}

template <typename T, size_t S>
T& Vector<T, S>::at(std::size_t index)
{
    if(index >= size) throw std::out_of_range("Out of range");

    return data[index];
}

template <typename T, size_t S>
const T& Vector<T, S>::at(std::size_t index) const
{
    if(index >= size) throw std::out_of_range("Out of range");

    return data[index];
}