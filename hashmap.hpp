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
    void remove(const K& key);
    bool contains(const K& key) const;
    
    V& operator[](const K& key);
    
    size_t size() const;
    bool empty() const;
};

#include "hashmap.ipp"

#endif // HASHMAP_HPP