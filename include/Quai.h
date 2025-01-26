#pragma once
#include "Stockage.h"

class Quai : public Stockage {
public:
    int nbTransporteur;

    Quai(int nbTransporteur, int capacite)
        : Stockage(capacite), nbTransporteur(nbTransporteur) {}
};
