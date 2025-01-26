#pragma once
#include <vector>
#include "Produit.h"

class Stockage {
protected:
    int capacite;
public:
    std::vector<Produit> produits;

    Stockage(int capacite) : capacite(capacite) {}

    int getCapacite() const { return capacite; }
};
