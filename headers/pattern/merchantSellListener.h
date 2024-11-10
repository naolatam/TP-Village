#ifndef MERCHANTSELLLISTENER_H
#define MERCHANTSELLLISTENER_H

class Merchant;

#include <list>

class MerchantSellListener {
public:
    virtual void notifySell(Merchant* m);
    virtual ~MerchantSellListener() = default;
    MerchantSellListener() {};

};



#endif // MERCHANTSELLLISTENER_H
