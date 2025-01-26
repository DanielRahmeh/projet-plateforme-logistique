#pragma once
#include "Region.h" // Pour utiliser la classe Region

class Client {
public:
    int id;
    Region region;

    Client() : id(0), region() {}

    Client(int id, const Region& region)
        : id(id), region(region) {}
};
