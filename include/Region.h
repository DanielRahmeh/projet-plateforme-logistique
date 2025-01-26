#pragma once
#include <vector>

class Region {
public:
    int id;
    std::string nom;

    Region() : id(0), nom("Undefined") {}

    Region(int id, std::string nom) : id(id), nom(nom) {}


};

std::vector<Region> genererRegionsFrancaises();