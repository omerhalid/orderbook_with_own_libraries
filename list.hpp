#pragma once

#include <stdexcept>
#include <iostream>
#include <memory>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;
        
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    std::unique_ptr<Node> head;
    Node* tail;
    size_t size_;

public:

    DoublyLinkedList();
    virtual ~DoublyLinkedList();

    void pushFront(T val);
    void pushBack(T val);
    void popFront();
    void popBack();
    void insert(T val, int index);
    remove(T val, int index);
    T at(int index);
    void erase();

};

#include "list.ipp"