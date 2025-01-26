#pragma once
#include <vector>
#include "Produit.h"
#include "Client.h"

class Commande {
public:
    int commandeID; 
    std::vector<int> refProduits;
    Client client;
    bool isLivred;

    Commande() 
        : commandeID(0), client(), isLivred(false) {}

    Commande(int id, const Client& client)
        : commandeID(id), client(client), isLivred(false) {}
};
