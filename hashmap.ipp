#include "hashmap.hpp"

template <typename K, typename V>
HashMap<K, V>::HashMap() : buckets(initial_capacity), size_(0) {}

template <typename K, typename V>
HashMap<K, V>::~HashMap()
{
    // we use RAII so no need to explicitly clear the memory.
    std::cout << "Destructed.\n";
}

template <typename K, typename V>
inline size_t HashMap<K, V>::hash(const K &key) const
{
    return std::hash<K>{}(key) % table.size();
}

template <typename K, typename V>
void HashMap<K, V>::resize()
{
    size_t newBuckets = table.size() * 2;
    std::vector<std::list<std::pair<K, V>>> newTable(newBuckets);

    for(const auto& bucket : table)
    {
        for(const auto& pair : bucket)
        {
            size_t newHashValue = hash(pair.first);
            newTable[newHashValue].push_back(pair);
        }
    }
}

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value)
{
    if(numElements / static_cast<float>table.size() > load_factor) resize();

    size_t hasValue = hash(key);
    auto& cell = table[hasValue];

    for(const auto& pair : cell)
    {
        if(pair.first == key)
            std::cout << "[WARNING] Key exists. Replaced." << std::endl; // replace it with exception?
            return
    }

    cell.emplace_back(key, value); // if i overload the [] operator would it help in this line?
    ++numElements;
}

template <typename K, typename V>
V HashMap<K, V>::get(const K& key) const
{
    size_t hasValue = hash(key);
    auto& cell = table[hasValue];

    for(const auto& pair : cell)
    {
        if(pair.first == key)
            return pair.second;
    }

    std::cout << "[WARNING] Key does not exist." << std::endl;
    return -1;
}

template <typename K, typename V>
void HashMap<K, V>::remove(const K& key)
{
    size_t hasValue = hash(key);
    auto& cell = table[hasValue];

    for(const auto& pair : cell)
    {
        if(pair.first == key)
            cell.erase(key, value); // if i overload the [] operator would it help in this line?
            --numElements;
    }

    std::cout << "[WARNING] Key does not exist." << std::endl; // throw expection might be better here.
    
}

template <typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const
{
    size_t hasValue = hash(key);
    auto& cell = table[hasValue];

    for(const auto& pair : cell)
    {
        if(pair.first == key)
           return true;
    }

    return false;
}

template <typename K, typename V>
V& HashMap<K, V>::operator[](const K& key)
{
    size_t hashValue = hash(key);
    auto& cell = table[hashValue];

    for(auto& pair : cell)
    {
        if(pair.first == key)
            return pair.second;
    }

    // If key does not exist, insert a default value
    cell.emplace_back(key, V());
    ++numElements;
    return cell.back().second;
}