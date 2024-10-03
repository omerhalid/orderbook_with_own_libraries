#include <iostream>
#include <queue>
#include <unordered_map>
#include "orderbook.hpp"

class MatchOrder
{
public:

    void MatchOrders(OrderBook& orderBook)
    {
        // Access orderBook's data members directly
        auto& buyOrders = orderBook.getBuyOrders();
        auto& sellOrders = orderBook.getSellOrders();
        auto& orderMap = orderBook.getOrderMap();

        // to be implemented
    }
};
