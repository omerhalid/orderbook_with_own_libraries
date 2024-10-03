#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <functional>
#include "vector.hpp"
#include "list.hpp"

template <typename K, typename V>
class HashMap {
private:
    static constexpr size_t initial_capacity = 16;
    static constexpr float load_factor = 0.75f;
    
    Vector<DoublyLinkedList<std::pair<K, V>>> table;
    size_t numElements;
    
    inline size_t hash(const K& key) const;
    void resize();

public:
    HashMap();
    ~HashMap() = default;
    
    // Delete copy constructor and assignment operator
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
    
    // Move constructor and assignment operator
    HashMap(HashMap&&) noexcept = default;
    HashMap& operator=(HashMap&&) noexcept = default;
    
    void insert(const K& key, const V& value);
    V& get(const K& key);
    const V& get(const K& key) const;
    void erase(const K& key);
    bool contains(const K& key) const;
    
    V& operator[](const K& key);
    
    size_t size() const;
    bool empty() const;

    // Iterator support
    class iterator;
    class const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    iterator find(const K& key);
    const_iterator find(const K& key) const;
};

template <typename K, typename V>
class HashMap<K, V>::iterator {
private:
    using BucketIterator = typename DoublyLinkedList<std::pair<K, V>>::iterator;
    using TableIterator = typename Vector<DoublyLinkedList<std::pair<K, V>>>::iterator;

    TableIterator tableIt;
    TableIterator tableEnd;
    BucketIterator bucketIt;

    void advanceToNextValid() {
        while (tableIt != tableEnd && bucketIt == tableIt->end()) {
            ++tableIt;
            if (tableIt != tableEnd) {
                bucketIt = tableIt->begin();
            }
        }
    }

public:
    iterator(TableIterator tableIt, TableIterator tableEnd)
        : tableIt(tableIt), tableEnd(tableEnd) {
        if (tableIt != tableEnd) {
            bucketIt = tableIt->begin();
            advanceToNextValid();
        }
    }

    std::pair<K, V>& operator*() {
        return *bucketIt;
    }

    std::pair<K, V>* operator->() {
        return &(*bucketIt);
    }

    iterator& operator++() {
        ++bucketIt;
        advanceToNextValid();
        return *this;
    }

    bool operator==(const iterator& other) const {
        return tableIt == other.tableIt && bucketIt == other.bucketIt;
    }

    bool operator!=(const iterator& other) const {
        return !(*this == other);
    }
};

template <typename K, typename V>
class HashMap<K, V>::const_iterator {
private:
    using BucketIterator = typename DoublyLinkedList<std::pair<K, V>>::const_iterator;
    using TableIterator = typename Vector<DoublyLinkedList<std::pair<K, V>>>::const_iterator;

    TableIterator tableIt;
    TableIterator tableEnd;
    BucketIterator bucketIt;

    void advanceToNextValid() {
        while (tableIt != tableEnd && bucketIt == tableIt->end()) {
            ++tableIt;
            if (tableIt != tableEnd) {
                bucketIt = tableIt->begin();
            }
        }
    }

public:
    const_iterator(TableIterator tableIt, TableIterator tableEnd)
        : tableIt(tableIt), tableEnd(tableEnd) {
        if (tableIt != tableEnd) {
            bucketIt = tableIt->begin();
            advanceToNextValid();
        }
    }

    const std::pair<K, V>& operator*() const {
        return *bucketIt;
    }

    const std::pair<K, V>* operator->() const {
        return &(*bucketIt);
    }

    const_iterator& operator++() {
        ++bucketIt;
        advanceToNextValid();
        return *this;
    }

    bool operator==(const const_iterator& other) const {
        return tableIt == other.tableIt && bucketIt == other.bucketIt;
    }

    bool operator!=(const const_iterator& other) const {
        return !(*this == other);
    }
};

#include "hashmap.ipp"

#endif // HASHMAP_HPP