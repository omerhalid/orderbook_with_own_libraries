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

    void addOrder(int id, double price, double quantity, bool isBuyOrder)
    {
        if(orderMap.find(id) != orderMap.end())
        {
            std::cout<<"Order has been already created.\n"; // do i need this?
        }

        Order newOrder(id, price, quantity, isBuyOrder);
        orderMap[id] = newOrder;

        if(isBuyOrder) buyOrders.push(newOrder);
        else sellOrders.push(newOrder);
    }
    void cancelOrder(int id);
    void modifyOrder(int id, double newPrice, double newQuantity);

    void matchOrder(); // will be moved to another.cpp
};