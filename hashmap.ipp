template <typename K, typename V>
HashMap<K, V>::HashMap() : table(initial_capacity), numElements(0) {}

template <typename K, typename V>
inline size_t HashMap<K, V>::hash(const K& key) const {
    return std::hash<K>{}(key) % table.size();
}

template <typename K, typename V>
void HashMap<K, V>::resize() {
    Vector<DoublyLinkedList<std::pair<K, V>>> newTable(table.size() * 2);
    
    for (size_t i = 0; i < table.size(); ++i) {
        for (const auto& pair : table[i]) {
            size_t newIndex = std::hash<K>{}(pair.first) % newTable.size();
            newTable[newIndex].pushBack(pair);
        }
    }
    
    table = std::move(newTable);
}

template <typename K, typename V>
void HashMap<K, V>::insert(const K& key, const V& value) {
    if (numElements >= table.size() * load_factor) {
        resize();
    }
    
    size_t index = hash(key);
    auto& bucket = table[index];
    
    for (auto& pair : bucket) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    
    bucket.pushBack(std::make_pair(key, value));
    ++numElements;
}

template <typename K, typename V>
V& HashMap<K, V>::get(const K& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    
    for (auto& pair : bucket) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
const V& HashMap<K, V>::get(const K& key) const {
    size_t index = hash(key);
    const auto& bucket = table[index];
    
    for (const auto& pair : bucket) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
void HashMap<K, V>::remove(const K& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            --numElements;
            return;
        }
    }
    
    throw std::out_of_range("Key not found");
}

template <typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const {
    size_t index = hash(key);
    const auto& bucket = table[index];
    
    for (const auto& pair : bucket) {
        if (pair.first == key) {
            return true;
        }
    }
    
    return false;
}

template <typename K, typename V>
V& HashMap<K, V>::operator[](const K& key) {
    size_t index = hash(key);
    auto& bucket = table[index];
    
    for (auto& pair : bucket) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    bucket.pushBack(std::make_pair(key, V()));
    ++numElements;
    return bucket.back().second;
}

template <typename K, typename V>
size_t HashMap<K, V>::size() const {
    return numElements;
}

template <typename K, typename V>
bool HashMap<K, V>::empty() const {
    return numElements == 0;
}