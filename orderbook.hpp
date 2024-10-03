#include <iostream>
#include <queue>
#include "order.hpp"
#include "hashmap.hpp"

class OrderBook
{
private:

    struct BuyOrderComperator
    {
        bool operator()(const Order& a, const Order& b) const
        {
            return (a.price < b.price) || (a.timestamp == b.timestamp);
        }
    };

    struct SellOrderComperator
    {
        bool operator()(const Order& a, const Order& b) const
        {
            return (a.price > b.price);
        }
    };

    HashMap<int, Order> orderMap;

    std::priority_queue<Order, std::vector<Order>, BuyOrderComperator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellOrderComperator> sellOrders;

public:

};