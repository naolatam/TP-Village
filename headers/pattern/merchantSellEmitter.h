#ifndef MERCHANTSELLEMITTER_H
#define MERCHANTSELLEMITTER_H

class Merchant;
#include <list>

#include "headers/pattern/merchantSellListener.h"

class MerchantSellEmitter {
protected:
    std::list<MerchantSellListener*> m_observers;  // Liste des observateurs

public:
    void addObserver(MerchantSellListener* obs) {
        m_observers.push_back(obs);
    }

    void removeObserver(MerchantSellListener* obs) {
        m_observers.remove(obs);
    }

    // Méthode pour notifier tous les observateurs d'une vente de potion
    void notifySellToObserver(Merchant* m) {
        for (MerchantSellListener* obs : m_observers) {
            obs->notifySell(m);
        }
    }
    MerchantSellEmitter() {};
    ~MerchantSellEmitter() {};

};



#endif // MERCHANTSELLEMITTER_H
