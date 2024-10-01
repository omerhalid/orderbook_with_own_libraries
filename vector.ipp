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
    // No need to manually do resource managemenet since we use RAII with smart pointers
    std::cout << "Destructor called" << std::endl;
}

// copy constructer
// This constructor creates a new CVector object as a copy of an existing one.
template <typename T, size_t S>
Vector<T, S>::Vector(const Vector& obj) : size(obj.size), capacity(obj.capacity) 
{
    if(obj.data)
    {
        data = std::make_unique<T[]>(obj.capacity);
        std::copy(obj.data.get(), obj.data.get() + obj.size, data.get());
    }
}

// copy assingment operator
// deep copy
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
    return *this
}

// move constructer
template <typename T, size_t S>
Vector<T, S>::Vector(Vector&& obj) noexcept : size(obj.size), capacity(obj.capacity), data(obj.data)
{
    obj.size = 0;
    obj.capacity = 0;
    obj.data = nullptr;
}

// move assignment operator
template <typename T, size_t S>
Vector<T, S>& Vector<T, S>::operator=(Vector&& obj) noexcept
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
    return *this
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
    if (reserveSize > this->capacity) resize(reserveSize);
}


