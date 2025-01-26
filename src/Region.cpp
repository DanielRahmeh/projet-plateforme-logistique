#include <vector>
#include <string>
#include "../include/Region.h"

// Fonction pour generer les departements français metropolitains
std::vector<Region> genererRegionsFrancaises() {
    std::vector<Region> regions;
    regions.emplace_back(0, "Plateforme"); // Region speciale pour la plateforme elle-meme

    // Noms des departements
    std::vector<std::string> nomsDepartements = {
        "Ain", "Aisne", "Allier", "Alpes-de-Haute-Provence", "Hautes-Alpes", "Alpes-Maritimes",
        "Ardeche", "Ardennes", "Ariege", "Aube", "Aude", "Aveyron", "Bouches-du-Rhône", "Calvados",
        "Cantal", "Charente", "Charente-Maritime", "Cher", "Correze", "Corse", "Côte-d'Or", 
        "Côtes-d'Armor", "Creuse", "Dordogne", "Doubs", "Drôme", "Eure", "Eure-et-Loir",
        "Finistere", "Gard", "Haute-Garonne", "Gers", "Gironde", "Herault", "Ille-et-Vilaine",
        "Indre", "Indre-et-Loire", "Isere", "Jura", "Landes", "Loir-et-Cher", "Loire", "Haute-Loire",
        "Loire-Atlantique", "Loiret", "Lot", "Lot-et-Garonne", "Lozere", "Maine-et-Loire", "Manche",
        "Marne", "Haute-Marne", "Mayenne", "Meurthe-et-Moselle", "Meuse", "Morbihan", "Moselle",
        "Nievre", "Nord", "Oise", "Orne", "Pas-de-Calais", "Puy-de-Dôme", "Pyrenees-Atlantiques",
        "Hautes-Pyrenees", "Pyrenees-Orientales", "Bas-Rhin", "Haut-Rhin", "Rhône", "Haute-Saône",
        "Saône-et-Loire", "Sarthe", "Savoie", "Haute-Savoie", "Paris", "Seine-Maritime",
        "Seine-et-Marne", "Yvelines", "Deux-Sevres", "Somme", "Tarn", "Tarn-et-Garonne", "Var",
        "Vaucluse", "Vendee", "Vienne", "Haute-Vienne", "Vosges", "Yonne", "Territoire de Belfort",
        "Essonne", "Hauts-de-Seine", "Seine-Saint-Denis", "Val-de-Marne", "Val-d'Oise"
    };

    for (int i = 1; i <= nomsDepartements.size(); ++i) {
        regions.emplace_back(i, nomsDepartements[i - 1]);
    }

    return regions;
}
