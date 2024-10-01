#include <list.hpp>

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {} 

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // No need for manual memory control since we use RAII with smart pointers
    std::cout<<"Destructed.\n";
} 

template<typename T>
void DoublyLinkedList<T>::pushFront(T val)
{
    
}

template<typename T>
void DoublyLinkedList<T>::pushBack(T val)
{
    
}


template<typename T>
void DoublyLinkedList<T>::popFront()
{
    
}


template<typename T>
void DoublyLinkedList<T>::popBack()
{
    
}

template<typename T>
void DoublyLinkedList<T>::insert(T val, int index)
{
    
}

template<typename T>
void DoublyLinkedList<T>::remove(T val, int index)
{
    
}

template<typename T>
T& DoublyLinkedList<T>::at(int index)
{
    
}

template<typename T>
void DoublyLinkedList<T>::erase(T val, int index)
{
    
}