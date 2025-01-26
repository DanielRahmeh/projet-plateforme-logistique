#pragma once

#include <vector>
#include <iostream>
#include "Produit.h"
#include "Region.h"
#include "Commande.h"

class Transporteur {
public:
    int id;
    int capacite;
    Region destination;
    std::vector<Produit> produits;
    int currentCommandeID;
    int itemsOnBoard;
    std::vector<int> refsAttendus; 

    Transporteur(int id, int capacite, Region destination);

    void afficherProduitsAttendus() const;

    Transporteur* trouverTransporteurParCommandeID(std::vector<Transporteur>& transporteurs, int commandeID);
};
