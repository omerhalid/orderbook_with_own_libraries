#include "orderbook.hpp"

template <typename Compare>
void OrderBook::removeFromHeap(std::priority_queue<Order, std::vector<Order>, Compare> &heap, int id)
{
    std::vector<Order> temp;

    while(!heap.empty())
    {
        Order top = heap.top();
        heap.pop();

        if(top.id != id)
        {
            temp.push_back(std::move(top));
        }
    }

    for(const auto& order : temp)
    {
        heap.push(std::move(order));
    }
}

void OrderBook::addOrder(int id, double price, double quantity, bool isBuyOrder)
{
    if(orderMap.find(id) != orderMap.end())
    {
        std::cout << "Order has been already created before.\n";
        return;
    }

    Order newOrder(id, price, quantity, isBuyOrder);
    orderMap[id] = newOrder;

    if(isBuyOrder) buyOrders.push(newOrder);
    else sellOrders.push(newOrder);

    // Call matchOrders to attempt to match the new order
    matcher.MatchOrders(*this);
}

void OrderBook::cancelOrder(int id)
{
    if(orderMap.find(id) != orderMap.end())
    {  
        Order cancelledOrder = std::move(orderMap[id]);

        try
        {
            orderMap.erase(id);
        }
        catch(const std::out_of_range& e)
        {
            std::cout << "Order not found: " << e.what() << std::endl;
        }

        if(cancelledOrder.isBuyOrder) removeFromHeap(buyOrders, id);
        else removeFromHeap(sellOrders, id);
    }
}

void OrderBook::modifyOrder(int id, double newPrice, double newQuantity)
{
    if(orderMap.find(id) != orderMap.end())
    {
        Order& order = orderMap[id];

        // Remove the order from the appropriate heap
        if(order.isBuyOrder) removeFromHeap(buyOrders, id);
        else removeFromHeap(sellOrders, id);

        // Update the order in the orderMap
        order.price = newPrice;
        order.quantity = newQuantity;

        // Add the updated order back to the appropriate heap
        if(order.isBuyOrder) buyOrders.push(order);
        else sellOrders.push(order);

        // Call matchOrders to attempt to match the modified order
        matcher.MatchOrders(*this);
    }
}

// Getter functions to provide access to private members
std::priority_queue<Order, std::vector<Order>, OrderBook::BuyOrderComperator>& OrderBook::getBuyOrders() { return buyOrders; }
std::priority_queue<Order, std::vector<Order>, OrderBook::SellOrderComperator>& OrderBook::getSellOrders() { return sellOrders; }
HashMap<int, Order>& OrderBook::getOrderMap() { return orderMap; }
