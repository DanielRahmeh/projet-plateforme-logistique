#pragma once
#include "Stockage.h"

class Entrepot : public Stockage {
public:
    Entrepot(int capacite) : Stockage(capacite) {}
};
