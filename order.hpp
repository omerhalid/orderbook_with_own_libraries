#include <iostream>
#include <chrono>

struct Order
{
    int id;
    double price;
    double quantity;
    bool isBuyOrder;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

    // Constructor for easier initialization
    Order(int id, double price, double quantity, bool isBuyOrder)
        : id(id), price(price), quantity(quantity), isBuyOrder(isBuyOrder), timestamp(std::chrono::system_clock::now()) {}
};
