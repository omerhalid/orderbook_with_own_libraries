#include <iostream>
#include "hashmap.hpp"

int main() {
    // Create a HashMap instance
    HashMap<int, std::string> map;

    // Insert some key-value pairs
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");

    // Retrieve and print values
    try {
        std::cout << "Key 1: " << map.get(1) << std::endl;
        std::cout << "Key 2: " << map.get(2) << std::endl;
        std::cout << "Key 3: " << map.get(3) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    // Check if keys exist
    std::cout << "Contains key 1: " << map.contains(1) << std::endl;
    std::cout << "Contains key 4: " << map.contains(4) << std::endl;

    // Remove a key
    map.remove(2);

    // Try to retrieve a removed key
    try {
        std::cout << "Key 2: " << map.get(2) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }

    // Use the subscript operator
    map[4] = "four";
    std::cout << "Key 4: " << map[4] << std::endl;

    return 0;
}