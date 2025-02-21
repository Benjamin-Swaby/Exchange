#include "include/number.hpp"


namespace ouch {


    void toNumber(ouch::number outprice, double price) {
        // [0,0,0,0,0,0 . 0,0,0,0]
        // decimal point will always be after 6 digits
        // 123.456 -> [0,0,0,1,2,3,4,5,6,0] -> [0,0,0,1,2,3, . 4,5,6,0]

        if (price < 0 || price > 999999.9999)
            return;


        // to achive 4 decimal places at the end we will x10^4 and then convert to integer.
        unsigned long intPrice = price * 10000;
        

        std::cout << price << "->" << intPrice << std::endl;

        for (int i = 1; intPrice != 0 && i >= 0; i++) {
            outprice[10 - i] = intPrice % 10;
            intPrice /= 10;
        }

    }
    
    std::pair<unsigned char*, size_t> toNumber(float price) {

        number outprice = {0,0,0,0,0,0,0,0,0,0};    

        toNumber(outprice, price);
        
        // return the price and the size of the price (this should always be 10 but just in case).
        return pair<unsigned char*, size_t>(outprice, 10);

    }

    std::ostream& operator<<(std::ostream& os, const number& num){

        for (size_t i = 0; i < 10; ++i) {
            if (i == 6) {
                os << " . ";
            }
            os << static_cast<char>(num[i] + 48);
        }
        return os;

    }


        


}