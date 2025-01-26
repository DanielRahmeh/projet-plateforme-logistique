#include <iostream>
#include "../include/Commande.h"
#include "../include/Transporteur.h"


Transporteur::Transporteur(int id, int capacite, Region destination)
    : id(id),
      capacite(capacite),
      destination(destination),
      currentCommandeID(0),
      itemsOnBoard(0)
{
}

// Affiche les références de produits que ce transporteur attend.

void Transporteur::afficherProduitsAttendus() const {
    std::cout << "Transporteur#" << id << " attend " 
              << refsAttendus.size() << " refs : ";
    for (int ref : refsAttendus) {
        std::cout << ref << " ";
    }
    std::cout << "\n";
}

// Retourne un pointeur vers le transporteur gérant la commandeID spécifiée, ou nullptr sinon.
Transporteur* trouverTransporteurParCommandeID(std::vector<Transporteur>& transporteurs, int commandeID) {
    for (auto &t : transporteurs) {
        if (t.currentCommandeID == commandeID) return &t;
    }
    return nullptr;
}