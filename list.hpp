#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>

// doubly linked list

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        std::unique_ptr<Node> prev;
        
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head;
    std::unique_ptr<Node> tail;
    size_t size_;

public:

    DoublyLinkedList();
    virtual ~DoublyLinkedList();

    void pushFront(T val);
    void pushBack(T val);
    void popFront();
    void popBack();
    void insert(T val, int index);
    void remove(int index);
    T& at(int index);
    bool contains(const T& value) const;
    void erase(const T& );
    bool empty() const;
    size_t size() const;

};

#include "list.ipp"