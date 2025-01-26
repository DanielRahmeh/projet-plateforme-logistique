#pragma once

#include <string>
#include "Plateforme.h"     // ou vos #includes nécessaires
#include "Region.h"
#include "Client.h"
#include "Commande.h"
#include "Transporteur.h"
#include "Manutention.h"
#include "Quai.h"
#include "Convoyeur.h"
#include "Entrepot.h"

class Simulation {
private:
    // --- Paramètres relatifs à la structure (transporteurs, manut, etc.) ---
    std::string regionInput; // 'dep' ou 'nb'
    int nbTransporteurs;
    int capaciteTransporteurs;
    int nbManutentions;
    int capaciteManutention;
    int nbConvoyeursEntree;
    int capaciteConvoyeursEntree;
    int nbConvoyeursSortie;
    int capaciteConvoyeursSortie;
    int capaciteQuaiEntree;
    int capaciteQuaiSortie;
    int capaciteEntrepot;

    // --- Paramètres relatifs à la simulation ---
    int horizonSimulation;
    int frequenceArrivage;
    int reference;
    int nombreClients;
    int frequenceCommande;
    int limiteCommande;

    // --- Conteneurs internes ---
    int currentDay;
    long long totalProductsGenerated;
    long long totalDelivered;

    // Les "niveaux"
    Quai quaiEntree;
    Quai quaiSortie;
    std::vector<Convoyeur> convoyeursEntree;
    std::vector<Convoyeur> convoyeursSortie;
    Entrepot entrepot;

    // Les acteurs
    std::vector<Transporteur> transporteurs;
    std::vector<Manutention> manutentions;

    // Données
    std::vector<Region> regions;
    std::vector<Client> clients;
    std::vector<Commande> commandesNonLivrees;
    static int nextCommandeID; // on le définira dans Simulation.cpp

public:
    // Constructeur
    Simulation(
        std::string regionInput,
        int nbTransporteurs,
        int capaciteTransporteurs,
        int nbManutentions,
        int capaciteManutention,
        int nbConvoyeursEntree,
        int capaciteConvoyeursEntree,
        int nbConvoyeursSortie,
        int capaciteConvoyeursSortie,
        int capaciteQuaiEntree,
        int capaciteQuaiSortie,
        int capaciteEntrepot,
        int horizonSimulation,
        int frequenceArrivage,
        int reference,
        int nombreClients,
        int frequenceCommande,
        int limiteCommande
    );

    // Méthode principale
    void run();

private:
    void afficherProduits(const std::string& prefix, const std::vector<Produit>& produits);
    void initRegions();
    void initClients();
};
