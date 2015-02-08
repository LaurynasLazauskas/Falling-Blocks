#ifndef BLOCK_BASKET_H_INCLUDED
#define BLOCK_BASKET_H_INCLUDED

#include <time.h>
#include "enum_names.h"

class BlocksBasket {
public:
    BlocksBasket() {
        fill();
    }
    void fill() {
        int tempBasket[7] = {B_S, B_Z, B_L, B_J, B_O, B_I, B_T};
        int indexTempBasket;
        int tempBasketSize = 7;
        basketSize = 7;

        for (int i = 0; i < 7; i++) {
            srand(time(NULL));
            indexTempBasket = rand() % tempBasketSize;
            basket[i] = tempBasket[indexTempBasket];
            for (int j = indexTempBasket; j < tempBasketSize; j++)
                tempBasket[j] = tempBasket[j+1];
            tempBasketSize--;
        }
    }
    int get() {
        if (basketSize == 0)
            fill();
        basketSize--;
        return basket[basketSize];
    }
    int peak() {
        if(basketSize == 0)
            fill();
        return basket[basketSize-1];
    }
    ~BlocksBasket() {
    }
private:
    int basketSize;
    int basket[7];
};


#endif
