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
