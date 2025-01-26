#pragma once
#include <vector>
#include "Produit.h"
#include "Quai.h"
#include "Convoyeur.h"
#include "Entrepot.h"
#include "Transporteur.h"

class Manutention {
public:
    int id;
    int capacite;
    bool affecteeACommande;
    int commandeID;
    std::vector<Produit> produits;


    Manutention(int id, int capacite)
        : id(id), capacite(capacite), affecteeACommande(false), commandeID(0)
    {}

    // Transférer jusqu'à x produits d'un stockage -> un autre
    int transfererProduits(Stockage& source, Stockage& cible, int x);

    // Transférer jusqu'à x produits d'un transporteur -> un stockage
    int transfererTransporteurToStockage(Transporteur& t, Stockage& s, int x);

    // Transférer jusqu'à x produits d'un stockage -> un transporteur
    int transfererStockageToTransporteur(Stockage& s, Transporteur& t, int x);
};
