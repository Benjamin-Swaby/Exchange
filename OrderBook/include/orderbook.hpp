#pragma once

#include <queue>
#include <map>
#include <utility>
#include <algorithm>
#include <set>

#include "order.hpp"


namespace OrderBook {

    

    class orderQueue : public std::priority_queue<InternalOrder, std::vector<InternalOrder>> {
        
    public:
        bool remove(const InternalOrder& order) {
            auto it = std::find_if(this->c.begin(), this->c.end(), [order](const InternalOrder& o) {
                return o.ID == order.ID;
            });

            if(it != this->c.end()) {
                
                this->c.erase(it);
                std::make_heap(this->c.begin(), this->c.end(), this->comp);
                return true;
            }
            return false;

        }


        bool remove(const uint64_t id) {

            auto it = std::find_if(this->c.begin(), this->c.end(), [id](const InternalOrder& order) {
                return order.ID == id;
            });

            if(it != this->c.end()) {
                this->c.erase(it);
                std::make_heap(this->c.begin(), this->c.end(), this->comp);
                return true;
            }
            return false;

        }

        uint32_t volume() {
            uint32_t sum = 0;
            for(auto &order : this->c) {
                sum += order.shares;
            }
            return sum;
        }

        InternalOrder* getByID(uint64_t id) {
            auto it = std::find_if(this->c.begin(), this->c.end(), [id](const InternalOrder& order) {
                return order.ID == id;
            });

            if (it != this->c.end())
                return &(*it);
            
            return nullptr;
        }

    };


    typedef std::pair<orderQueue, orderQueue> orderLevel;
    /**
     *      OrderBook for Stock
     *    Buy      Price      Sell
     * [1,2,3,4,5] : 1 : [1,2,3,4,5]
     * [1,2,3,4,5] : 2 : [1,2,3,4,5]
     * [1,2,3,4,5] : 3 : [1,2,3,4,5]
     * [1,2,3,4,5] : 4 : [1,2,3,4,5]
     *     ...      ...      ...
     */


    class StockOrderBook {
    private:
        std::map<uint32_t, orderLevel> Orders;
        orderQueue global_pq;

        uint64_t ticker;

        

    public:

        void insert(OrderBook::InternalOrder order);
        void remove(OrderBook::InternalOrder order);
        void remove (uint64_t orderID);
        InternalOrder* getByID(uint64_t orderID);
        void modify(OrderBook::InternalOrder* order, uint32_t newShares);

        void match_all();
        uint32_t match();

        std::pair<uint32_t, uint32_t> volumeAtPrice(uint32_t price);
        uint32_t midPrice();
        uint32_t latency();


        StockOrderBook(uint64_t stock);
        ~StockOrderBook() = default;

       
        friend std::ostream& operator<<(std::ostream& os, StockOrderBook& sOB) {

        
            union {
                uint64_t ticker;
                char str[8];
            } convert;

            convert.ticker = sOB.ticker;

            os << "\t\t------------------------------" << std::endl;
            os << "\t\t\t" << convert.str <<std::endl;
            for(auto &it : sOB.Orders) {
                os << "\tPrice: " << it.first << '\t';
                os << "\tBuy: " <<  sOB.volumeAtPrice(it.first).first << '\t';
                os << "\tSell: " << sOB.volumeAtPrice(it.first).second << std::endl;
            }
            os << "\t\t------------------------------" << std::endl;

            return os;

        }


    

    };


}