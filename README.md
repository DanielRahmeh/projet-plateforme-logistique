# projet-plateforme-logistique

Ce projet implémente une simulation d’une plateforme logistique avec différentes entités : transporteurs, manutentions, quai d’entrée/sortie, convoyeurs, entrepôt, etc. L’objectif est de modéliser la réception de produits, leur stockage et leur distribution vers les clients.

## Sommaire
1. [Prérequis](#prérequis)  
2. [Installation](#installation)  
3. [Compilation](#compilation)  
4. [Exécution](#exécution)  
5. [Utilisation de la simulation](#utilisation-de-la-simulation)

---

## Prérequis

- Un **compilateur C++** supportant au moins le standard **C++17** (g++ >= 7, clang >= 6, etc.).
- L’outil **CMake** (version 3.10 ou supérieure).
- Un système GNU/Linux (ou macOS, ou Windows avec un environnement CMake compatible).

---

## Installation

1. **Cloner** ce dépôt ou récupérer les sources :

   ```bash
   git clone https://github.com/DanielRahmeh/projet-plateforme-logistique

2. **Créer** un répertoire de build :

   
    ```bash
    mkdir build
    cd build
    ```

---

## Compilation

À l’intérieur du dossier `build`, exécutez :

    cmake ..
    make

- `cmake ..` : génère les scripts de compilation à partir du fichier **CMakeLists.txt** situé à la racine (un niveau au-dessus, `..`).
- `make` : compile les sources et produit l’exécutable.

Si tout se passe bien, vous obtiendrez un fichier exécutable nommé **`projet`** (ou le nom défini dans `add_executable`).

---

## Exécution

Toujours dans le dossier `build`, lancez :

    ./projet

L’application vous demandera alors divers paramètres (nombre de transporteurs, capacité, etc.) avant de démarrer la simulation.  
Il vous suffira de suivre les instructions **interactives** (saisies au clavier) pour lancer et faire avancer la simulation jour après jour.

---

## Utilisation de la simulation

1. **Lancement** :  
   Saisissez les paramètres demandés :
   - `dep` ou un nombre pour la génération des régions.
   - Nombre de transporteurs, capacité, etc.
   - Nombre de clients, fréquence d’arrivage, etc.

2. **Simulation** :  
   Le programme affiche un résumé de ce qu’il se passe chaque jour (arrivage, commandes passées, transferts de manutentions, etc.).  
   À la fin de chaque journée, vous décidez si vous souhaitez :
   - Passer au jour suivant (`n`),
   - Quitter la simulation (`q`).

3. **Fin** :  
   Soit vous atteignez l’**horizon de simulation** (nombre de jours limite) et la simulation s’arrête automatiquement, soit vous tapez `q` pour arrêter manuellement.
   
