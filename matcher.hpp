#include <iostream>
#include <queue>
#include <unordered_map>
#include "orderbook.hpp"

class MatchOrder
{
public:
    void MatchOrders(std::priority_queue<Order, std::vector<Order>, OrderBook::BuyOrderComperator>& buyOrders,
                     std::priority_queue<Order, std::vector<Order>, OrderBook::SellOrderComperator>& sellOrders,
                     std::unordered_map<int, Order>& orderMap)
    {
        // to be implemented
    }
};