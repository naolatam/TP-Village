#ifndef SHOP_H
#define SHOP_H

#include "headers/locations/buildings/building.h"
#include "headers/pattern/merchantSellListener.h"
#include "headers/entity/merchant.h"


class Shop : public Building, public MerchantSellListener
{
private:
    vector<Merchant*> m_merchants;

public:
    Shop(Game& game);

    void enter();
    void inside();
    void interactWithMerchant();
    void interactWithMerchant(int mIdx);
    void sellPotion();


    void notifySell(Merchant* m);
    Potion* getPotionFromShopStock() const;

    ~Shop();
};

#endif // SHOP_H
