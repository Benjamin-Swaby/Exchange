#include "include/orderbook.hpp"


namespace OrderBook {


    StockOrderBook::StockOrderBook(uint64_t stock) {
        ticker = stock;
        this->global_pq = orderQueue();
    }


    void StockOrderBook::insert(OrderBook::InternalOrder order) {

        //std::cout << "IN:\t" << order << std::endl;
        
        if (!this->Orders.contains(order.price)) {
            // initialise the order level
            this->Orders[order.price] = {orderQueue(), orderQueue()};
        }

        orderQueue* queue = &this->Orders[order.price].first;


        if(order.side == 'S') 
            queue = &this->Orders[order.price].second;

        queue->push(order);
        this->global_pq.push(order); // push to global priority queue

    }


    void StockOrderBook::remove(OrderBook::InternalOrder order) {

        //std::cout << "OUT:\t" << order << std::endl;

        // price level cannot be found - remove order
        if (!this->Orders.contains(order.price)) {
            return;
        }
        
        orderQueue* queue = &this->Orders[order.price].first;

        if(order.side == 'S') 
            queue = &this->Orders[order.price].second;

        queue->remove(order);
        global_pq.remove(order);

    }

    void StockOrderBook::remove(uint64_t ID) {

        std::cout << "OUT:\t" << ID << std::endl;
        auto io = global_pq.getByID(ID);
        global_pq.remove(ID);
        this->remove(*io);

    }

    
    inline InternalOrder* StockOrderBook::getByID(uint64_t ID) {
        return global_pq.getByID(ID);
    }



    void StockOrderBook::match_all() {

        uint32_t number_of_unmatchable = 0;

        while(number_of_unmatchable < this->global_pq.size()) {
            uint32_t filled = this->match();
            
            if (filled == 0) {
                number_of_unmatchable++;
            }
            
        }
        


    }


    uint32_t StockOrderBook::match() {
        
        if (global_pq.empty())
            return 0;

        uint32_t filledCycle = 0;

        // Order to match
        InternalOrder target = global_pq.top();
        std::cout << "Target: " <<target << std::endl;
        InternalOrder toFill;
        this->remove(target);

        //auto begin = (target.side == 'B') ? this->Orders.begin() : this->Orders.rbegin();
        //auto end = this->Orders.end();
        
        if (target.side == 'B') {
            auto level = this->Orders.begin(); // start at lowest price

            for(level; level != this->Orders.end() && level->first <= target.price; level++) {

                if(level->second.second.empty()) continue; // no sell orders at this level

                auto toFill = level->second.second.top(); // highest priority sell order on that level.
                this->remove(toFill);

                auto filled = toFill.fillAgainst(&target); // fill against the target order
                filledCycle += filled;
                toFill.filled += filled;
                toFill.fillPrice += filled * toFill.price;
                target.fillPrice += filled * toFill.price;
                //std::cout << "Filled: " << filled << " Against: " << toFill << std::endl;


                if (toFill.shares > 0) {
                    toFill.timestamp = nanoseconds_since_midnight();
                    this->insert(toFill);
                }


            }


        } else if (target.side == 'S') {
            auto level = this->Orders.rbegin(); // start at highest price

            for (level; level != this->Orders.rend() && level->first >= target.price; level++) {
                
                if(level->second.first.empty()) continue; // no buy orders at this level

                auto toFill = level->second.first.top(); // highest priority buy order on that level.
                this->remove(toFill);

                auto filled = toFill.fillAgainst(&target); // fill against the target order
                filledCycle += filled;
                toFill.filled += filled;
                toFill.fillPrice += filled * toFill.price;
                target.fillPrice += filled * toFill.price;

                //std::cout << "Filled: " << filled << " Against: " << toFill << std::endl;

                if (toFill.shares > 0) {
                    toFill.timestamp = nanoseconds_since_midnight();
                    this->insert(toFill);
                }


            }

        }

        
        if (target.shares > 0) {
            target.timestamp = nanoseconds_since_midnight(); // reinsert at current timestamp
            this->insert(target);
        }

        return filledCycle;

    }

    std::pair<uint32_t, uint32_t> StockOrderBook::volumeAtPrice(uint32_t price) {

        orderQueue* buy = &this->Orders[price].first;
        orderQueue* sell = &this->Orders[price].second;

        return {buy->volume(), sell->volume()};
    }


    uint32_t StockOrderBook::midPrice() {

        if(this->Orders.empty()) return 0;

        uint32_t maxPrice = 0;
        uint32_t minPrice = std::numeric_limits<uint32_t>::max();


        for(auto &it : this->Orders) {

            auto volumeAtLevel = this->volumeAtPrice(it.first);
            if(volumeAtLevel.first == 0 && volumeAtLevel.second == 0)
                continue;

            maxPrice = (it.first > maxPrice) ? it.first : maxPrice;
            minPrice = (it.first < minPrice) ? it.first : minPrice;
        }


        if(minPrice != std::numeric_limits<uint32_t>::max())
            return (maxPrice + minPrice) / 2;
        else
            return 0;

    }



}