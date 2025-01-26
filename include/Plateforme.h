#pragma once
#include <vector>
#include "Transporteur.h"
#include "Manutention.h"
#include "Quai.h"
#include "Convoyeur.h"
#include "Entrepot.h"

class Plateforme {
public:
    std::vector<Transporteur> transporteurs;
    std::vector<Manutention> manutentions;
    std::vector<Convoyeur> convoyeursEntree;
    std::vector<Convoyeur> convoyeursSortie;
    Quai quaiEntree;
    Quai quaiSortie;
    Entrepot entrepot;
    int heure;

    Plateforme(int nbTransporteurs, int capaciteTransporteurs,
               int nbManutentions, int capaciteManutention,
               int nbConvoyeursEntree, int capaciteConvoyeursEntree,
               int nbConvoyeursSortie, int capaciteConvoyeursSortie,
               int capaciteQuaiEntree, int capaciteQuaiSortie,
               int capaciteEntrepot);
};