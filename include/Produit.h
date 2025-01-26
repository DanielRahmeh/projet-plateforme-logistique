#pragma once
#include <string>

class Produit {
public:
    int id;
    std::string nom;
    int reference;
    int destination;
    int temps;

    Produit(int id, const std::string& nom, int reference, int destination)
        : id(id), nom(nom), reference(reference), destination(destination), temps(0) {}
};