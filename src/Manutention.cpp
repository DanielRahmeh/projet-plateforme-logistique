#include "../include/Manutention.h"

/**
 * Transfère jusqu'à x produits d'un stockage source vers un stockage cible.
 */
int Manutention::transfererProduits(Stockage& source, Stockage& cible, int x) {
    int count = 0;
    while (count < x) {
        if (source.produits.empty()) break;
        if ((int)cible.produits.size() >= cible.getCapacite()) break;

        Produit p = source.produits.back();
        source.produits.pop_back();
        cible.produits.push_back(p);
        count++;
    }
    return count;
}

/**
 * Transfère jusqu'à x produits d'un transporteur vers un stockage.
 */
int Manutention::transfererTransporteurToStockage(Transporteur& t, Stockage& s, int x) {
    int count = 0;
    while (count < x) {
        if (t.produits.empty()) break;
        if ((int)s.produits.size() >= s.getCapacite()) break;

        Produit p = t.produits.back();
        t.produits.pop_back();
        s.produits.push_back(p);
        count++;
    }
    return count;
}

/**
 * Calcule le nombre de produits 'ref' encore nécessaires au transporteur.
 */
static int countNeededRefs(const Transporteur& t, int ref) {
    int totalNeeded = 0;
    for (int r : t.refsAttendus) {
        if (r == ref) totalNeeded++;
    }
    int alreadyHave = 0;
    for (auto &p : t.produits) {
        if (p.reference == ref) alreadyHave++;
    }
    return totalNeeded - alreadyHave; 
}

/**
 * Transfère jusqu'à x produits d'un stockage vers un transporteur en vérifiant ses besoins.
 */
int Manutention::transfererStockageToTransporteur(Stockage& s, Transporteur& t, int x) {
    int count = 0;

    while (count < x) {
        if (s.produits.empty()) break;
        if ((int)t.produits.size() >= t.capacite) break;

        Produit &p = s.produits.back();
        int stillNeeded = countNeededRefs(t, p.reference);

        if (stillNeeded > 0) {
            t.produits.push_back(p);
            s.produits.pop_back(); 
            count++;
        } else {
            break;
        }
    }

    return count;
}
