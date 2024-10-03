#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <iostream>
#include <queue>
#include "order.hpp"
#include "matcher.hpp"
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

    template <typename Compare>
    void removeFromHeap(std::priority_queue<Order, std::vector<Order>, Compare> &heap, int id);

    HashMap<int, Order> orderMap;

    std::priority_queue<Order, std::vector<Order>, BuyOrderComperator> buyOrders;
    std::priority_queue<Order, std::vector<Order>, SellOrderComperator> sellOrders;

    MatchOrder matcher;

public:

    void addOrder(int id, double price, double quantity, bool isBuyOrder);
    void cancelOrder(int id);
    void modifyOrder(int id, double newPrice, double newQuantity);

    // Getter functions to provide access to private members
    std::priority_queue<Order, std::vector<Order>, BuyOrderComperator>& getBuyOrders();
    std::priority_queue<Order, std::vector<Order>, SellOrderComperator>& getSellOrders();
    HashMap<int, Order>& getOrderMap();
};

#endif // ORDERBOOK_HPP
