#include <iostream>
#include <chrono>

struct Order
{
    int id;
    double quantity;
    bool isBuyOrder;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

    // Constructor for easier initialization
    Order(int id, double quantity, bool isBuyOrder, std::chrono::time_point<std::chrono::system_clock> timestamp)
        : id(id), quantity(quantity), isBuyOrder(isBuyOrder), timestamp(timestamp) {}
};