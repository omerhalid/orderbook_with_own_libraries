#include <vector>
#include <list>
#include <stdexcept>
#include <iostream>

template <typename K, typename V>
class HashMap
{
private:
    std::vector<std::list<std::pair<K, V>>> table;
    int numElements;
    size_t size_;
    static const size_t initial_capacity = 16;
    static constexpr float load_factor = 0.75f;

    size_t hash(const K& key) const; // Hash function to map keys to bucket indices
    void resize(); // Resize function to handle rehashing

public:
    HashMap(); // Constructor
    virtual ~HashMap(); // Destructor

    void insert(const K& key, const V& value); // Insert key-value pair
    V get(const K& key) const; // Get value by key
    void remove(const K& key); // Remove key-value pair
    bool contains(const K& key) const; // Check if key exists

    V& operator[](const K& key); // Access value by key
};

#include "hashmap.ipp"