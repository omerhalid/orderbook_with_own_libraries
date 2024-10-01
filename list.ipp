#include "list.hpp"

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size_(0) {}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    // No need for manual memory control since we use RAII with smart pointers
    std::cout << "Destructed.\n";
}

template<typename T>
void DoublyLinkedList<T>::pushFront(T val)
{
    auto newNode = std::make_unique<Node>(val);
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->next = std::move(head);
        newNode->next->prev = newNode.get();
        head = std::move(newNode);
    }
    size_++;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(T val)
{
    auto newNode = std::make_unique<Node>(val);
    if (!head)
    {
        head = std::move(newNode);
        tail = head.get();
    }
    else
    {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    size_++;
}

template<typename T>
void DoublyLinkedList<T>::popFront()
{
    if (!head) throw std::runtime_error("List is empty");

    auto newHead = std::move(head->next);
    if (newHead)
    {
        newHead->prev = nullptr;
    }
    else
    {
        tail = nullptr; // List is now empty
    }
    head = std::move(newHead);
    size_--;
}

template<typename T>
void DoublyLinkedList<T>::popBack()
{
    if (!head) throw std::runtime_error("List is empty");

    auto newTail = tail->prev;
    if (newTail)
    {
        newTail->next.reset();
    }
    else
    {
        head.reset(); // List is now empty
    }
    tail = newTail;
    size_--;
}

template<typename T>
void DoublyLinkedList<T>::insert(T val, int index)
{
    if (index < 0 || index > size_) throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        pushFront(val);
        return;
    }

    if (index == size_)
    {
        pushBack(val);
        return;
    }

    auto newNode = std::make_unique<Node>(val);
    Node* temp = head.get();

    for (int i = 0; i < index; ++i)
    {
        temp = temp->next.get();
    }

    newNode->prev = temp->prev;
    newNode->next = std::move(temp->prev->next);
    temp->prev->next = std::move(newNode);
    temp->prev = temp->prev->next.get();

    size_++;
}

template<typename T>
void DoublyLinkedList<T>::remove(int index)
{
    if (index < 0 || index >= size_) throw std::out_of_range("Index out of range");

    if (index == 0)
    {
        popFront();
        return;
    }

    if (index == size_ - 1)
    {
        popBack();
        return;
    }

    Node* temp = head.get();
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next.get();
    }

    temp->prev->next = std::move(temp->next);
    if (temp->next)
    {
        temp->next->prev = temp->prev;
    }

    size_--;
}

template<typename T>
T& DoublyLinkedList<T>::at(int index)
{
    if (index < 0 || index >= size_) throw std::out_of_range("Index out of range");

    Node* temp = head.get();
    for (int i = 0; i < index; ++i)
    {
        temp = temp->next.get();
    }

    return temp->data;
}

template<typename T>
bool DoublyLinkedList<T>::contains(const T& value) const
{
    if (!head) throw std::runtime_error("List is empty");

    Node* temp = head.get(); // Use a raw pointer to traverse the list

    while (temp != nullptr)
    {
        if (temp->data == value) return true;
        temp = temp->next.get(); // Move to the next node
    }

    return false;
}

template<typename T>
void DoublyLinkedList<T>::erase(const T& value)
{
    if (!head) throw std::runtime_error("List is empty");

    Node* current = head.get();

    while (current != nullptr)
    {
        if (current->data == value)
        {
            // If the node to be erased is the head
            if (current == head.get())
            {
                head = std::move(head->next);
                if (head)
                {
                    head->prev = nullptr;
                }
                else
                {
                    tail = nullptr; // List is now empty
                }
            }
            // If the node to be erased is the tail
            else if (current == tail)
            {
                tail = tail->prev;
                tail->next.reset();
            }
            // If the node to be erased is in the middle
            else
            {
                current->prev->next = std::move(current->next);
                if (current->next)
                {
                    current->next->prev = current->prev;
                }
            }

            size_--;
            return;
        }
        current = current->next.get();
    }

    throw std::runtime_error("Value not found in the list");
}

// Utility functions
template<typename T>
bool DoublyLinkedList<T>::empty() const { return size_ == 0; }

template<typename T>
size_t DoublyLinkedList<T>::size() const { return size_; }