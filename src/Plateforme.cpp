#include "../include/Plateforme.h"

Plateforme::Plateforme(int nbTransporteurs, int capaciteTransporteurs,
                       int nbManutentions, int capaciteManutention,
                       int nbConvoyeursEntree, int capaciteConvoyeursEntree,
                       int nbConvoyeursSortie, int capaciteConvoyeursSortie,
                       int capaciteQuaiEntree, int capaciteQuaiSortie,
                       int capaciteEntrepot)
    : quaiEntree(0, capaciteQuaiEntree), quaiSortie(0, capaciteQuaiSortie),
      entrepot(capaciteEntrepot), heure(0) {

    // Initialiser les transporteurs
    for (int i = 0; i < nbTransporteurs; ++i) {
        Region regionParDefaut(0, "Plateforme");
        transporteurs.emplace_back(i, capaciteTransporteurs, regionParDefaut);
    }

    // Initialiser les manutentions
    for (int i = 0; i < nbManutentions; ++i) {
        manutentions.emplace_back(i, capaciteManutention);
    }

    // Initialiser les convoyeurs vers entrée
    for (int i = 0; i < nbConvoyeursEntree; ++i) {
        convoyeursEntree.emplace_back(capaciteConvoyeursEntree);
    }

    // Initialiser les convoyeurs vers sortie
    for (int i = 0; i < nbConvoyeursSortie; ++i) {
        convoyeursSortie.emplace_back(capaciteConvoyeursSortie);
    }
}
