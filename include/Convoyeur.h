#pragma once
#include "Stockage.h"

class Convoyeur : public Stockage {
public:
    Convoyeur(int capacite) : Stockage(capacite) {}
};
