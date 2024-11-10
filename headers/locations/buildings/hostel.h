#ifndef HOSTEL_H
#define HOSTEL_H

#include <thread>

#include "headers/locations/buildings/building.h"

class Hostel : public Building
{
    int m_basePrice;
    int m_maxPrice;
public:
    Hostel(Game& game);

    void enter();
    void inside();
    void sleep();
    ~Hostel() {};
};

#endif // HOSTEL_H
