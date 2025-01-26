#include <iostream>
#include <string>
#include "include/Simulation.h"

int main() {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale(""));

    // 1) Lecture entrée utilisateur
    std::cout << "Combien de regions ? (dep ou nb) : ";
    std::string input;
    std::cin >> input;

    int nbTransporteurs, capaciteTransporteurs;
    std::cout << "Nombre de transporteurs : ";
    std::cin >> nbTransporteurs;
    std::cout << "Capacite transporteurs : ";
    std::cin >> capaciteTransporteurs;

    int nbManutentions, capaciteManutention;
    std::cout << "Nombre de manutentions : ";
    std::cin >> nbManutentions;
    std::cout << "Capacite manutentions : ";
    std::cin >> capaciteManutention;

    int nbConvoyeursEntree, capaciteConvoyeursEntree;
    int nbConvoyeursSortie, capaciteConvoyeursSortie;
    std::cout << "Nombre convoyeurs entree : ";
    std::cin >> nbConvoyeursEntree;
    std::cout << "Capacite convoyeurs entree : ";
    std::cin >> capaciteConvoyeursEntree;

    std::cout << "Nombre convoyeurs sortie : ";
    std::cin >> nbConvoyeursSortie;
    std::cout << "Capacite convoyeurs sortie : ";
    std::cin >> capaciteConvoyeursSortie;

    int capaciteQuaiEntree, capaciteQuaiSortie, capaciteEntrepot;
    std::cout << "Capacite quai entree : ";
    std::cin >> capaciteQuaiEntree;
    std::cout << "Capacite quai de sortie : ";
    std::cin >> capaciteQuaiSortie;
    std::cout << "Capacite entrepot : ";
    std::cin >> capaciteEntrepot;

    int horizonSimulation, frequenceArrivage, reference;
    int nombreClients, frequenceCommande, limiteCommande;
    std::cout << "\nHorizon simulation (jours) : ";
    std::cin >> horizonSimulation;
    std::cout << "Frequence d'arrivage (tous les x jours) : ";
    std::cin >> frequenceArrivage;
    std::cout << "Nombre de references produits possibles : ";
    std::cin >> reference;
    std::cout << "Nombre de clients : ";
    std::cin >> nombreClients;
    std::cout << "Frequence de commande (1..100) : ";
    std::cin >> frequenceCommande;
    std::cout << "Nb produits max par commande : ";
    std::cin >> limiteCommande;

    // 2) Création d'un objet Simulation avec tous les paramètres
    Simulation sim(
        input,
        nbTransporteurs,
        capaciteTransporteurs,
        nbManutentions,
        capaciteManutention,
        nbConvoyeursEntree,
        capaciteConvoyeursEntree,
        nbConvoyeursSortie,
        capaciteConvoyeursSortie,
        capaciteQuaiEntree,
        capaciteQuaiSortie,
        capaciteEntrepot,
        horizonSimulation,
        frequenceArrivage,
        reference,
        nombreClients,
        frequenceCommande,
        limiteCommande
    );

    // 3) Lancement de la simulation
    sim.run();

    return 0;
}
