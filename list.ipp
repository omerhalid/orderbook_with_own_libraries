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
    std::unique_ptr<Node> newNode = std::make_unique(val);
    if(!head)
    {
        head = tail = newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size_ ++;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(T val)
{
    std::unique_ptr<Node> newNode = std::make_unique(val);

    if(!head)
    {
        head = tail = newNode;
    }

    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;

    size_ ++;
}


template<typename T>
void DoublyLinkedList<T>::popFront()
{
    if(!head) throw std::runtime_error("List is empty");

    auto newHead = std::move(head->next);

    if(newHead)
        newHead->prev = nullptr;
    else
        tail = nullptr; // list is now empty

    head = std::move(newHead);

    size_ --;
    
}


template<typename T>
void DoublyLinkedList<T>::popBack()
{
    if(!head) throw std::runtime_error("List is empty");

    auto newTail = std::move(tail->prev);

    if(newTail)
        newTail->next = nullptr;
    else
        head = nullptr; // list is now empty;

    tail = std::move(newTail);

    size_ --;
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