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