#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>

#include "../include/Simulation.h"
#include "../include/Region.h"
#include "../include/Produit.h"

int Simulation::nextCommandeID = 1;

// ------------------------------------------------
//  Constructeur de la SIMULATION
// ------------------------------------------------

Simulation::Simulation(
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
)
: regionInput(regionInput),
  nbTransporteurs(nbTransporteurs),
  capaciteTransporteurs(capaciteTransporteurs),
  nbManutentions(nbManutentions),
  capaciteManutention(capaciteManutention),
  nbConvoyeursEntree(nbConvoyeursEntree),
  capaciteConvoyeursEntree(capaciteConvoyeursEntree),
  nbConvoyeursSortie(nbConvoyeursSortie),
  capaciteConvoyeursSortie(capaciteConvoyeursSortie),
  capaciteQuaiEntree(capaciteQuaiEntree),
  capaciteQuaiSortie(capaciteQuaiSortie),
  capaciteEntrepot(capaciteEntrepot),
  horizonSimulation(horizonSimulation),
  frequenceArrivage(frequenceArrivage),
  reference(reference),
  nombreClients(nombreClients),
  frequenceCommande(frequenceCommande),
  limiteCommande(limiteCommande),
  currentDay(0),
  totalProductsGenerated(0),
  totalDelivered(0),
  quaiEntree(0, capaciteQuaiEntree),
  quaiSortie(0, capaciteQuaiSortie),
  entrepot(capaciteEntrepot)
{
    std::srand((unsigned)std::time(nullptr));

    // 1) Regions
    if(regionInput == "dep"){
        regions = genererRegionsFrancaises();
        int rcount = (int)regions.size() - 1;
        std::cout << rcount << " departements generes.\n";
    } else {
        int nbReg = std::stoi(regionInput);
        regions.emplace_back(0,"Plateforme");
        for(int i=1; i<=nbReg; i++){
            std::string rname;
            std::cout << "Nom region " << i << " : ";
            std::cin >> rname;
            regions.emplace_back(i, rname);
        }
    }

    // 2) Création des transporteurs
    transporteurs.reserve(nbTransporteurs);
    for(int i=1; i<=nbTransporteurs; i++){
        transporteurs.emplace_back(i, capaciteTransporteurs, regions[0]);
    }

    // 3) Création des manutentions
    manutentions.reserve(nbManutentions);
    for(int i=1; i<=nbManutentions; i++){
        manutentions.emplace_back(i, capaciteManutention);
    }

    // 4) Création des Convoyeurs
    convoyeursEntree.reserve(nbConvoyeursEntree);
    for(int i=0; i<nbConvoyeursEntree; i++){
        convoyeursEntree.emplace_back(capaciteConvoyeursEntree);
    }
    convoyeursSortie.reserve(nbConvoyeursSortie);
    for(int i=0; i<nbConvoyeursSortie; i++){
        convoyeursSortie.emplace_back(capaciteConvoyeursSortie);
    }

    // 5) Création des Clients
    clients.reserve(nombreClients);
    int nbRegionsReels = (int)regions.size() - 1; // hors Plateforme
    for(int i=1; i<=nombreClients; i++){
        if(nbRegionsReels > 0){
            int ridx = 1+(std::rand()%nbRegionsReels);
            clients.emplace_back(i, regions[ridx]);
        } else {
            clients.emplace_back(i, regions[0]);
        }
    }

}

// -------------------------------------------------
//  Méthode run() : la boucle de simulation
// -------------------------------------------------
void Simulation::run() {
    static int nextProductID = 1;

    while(true) {
        std::ostringstream dailyLog;
        std::ostringstream dailyLogCommandes;

        // (1) Jour
        std::cout << "\n===== JOUR " << currentDay << " / " << horizonSimulation << " =====\n";
        if(currentDay==horizonSimulation){
            std::cout << "Fin simulation.\n";
            break;
        }

        // ---------- ARRIVAGE ----------
        if(frequenceArrivage>0 && currentDay>0 && (currentDay%frequenceArrivage==0)){
            dailyLog << "[ARRIVAGE] Produits sur transporteurs libres\n";
            for(auto &t : transporteurs){
                if(t.currentCommandeID==0 && t.itemsOnBoard==0 && t.produits.empty()){
                    for(int i=0; i<t.capacite;i++){
                        int refp= 1+(std::rand()%reference);
                        std::string pname= "Produit"+std::to_string(nextProductID);
                        Produit prod(nextProductID++, pname, refp, 0);
                        t.produits.push_back(prod);
                        totalProductsGenerated++;
                    }
                    dailyLog << "Transporteur "<< t.id 
                             <<" recoit "<< t.produits.size() <<" produits.\n";
                }
            }
        }

        // ---------- GENERATION DE COMMANDES ----------
        std::vector<Commande> commandesDuJour;
        commandesDuJour.reserve(nombreClients);

        for(auto &cl : clients){
            int chance= std::rand()%100 +1;
            if(chance<= frequenceCommande){
                // On crée une nouvelle commande
                Commande ccmd(nextCommandeID++, cl);
                int nbp= 1+(std::rand()% limiteCommande);
                for(int i=0;i<nbp;i++){
                    int rr=1+(std::rand()%reference);
                    ccmd.refProduits.push_back(rr);
                }
                std::sort(ccmd.refProduits.begin(), ccmd.refProduits.end());
                
                // On place la commande dans commandesDuJour ET dans commandesNonLivrees
                commandesDuJour.push_back(ccmd);
                commandesNonLivrees.push_back(ccmd);
            }
        }

        // Stocke les commandes du jour dans dailyLogCommandes
        if(!commandesDuJour.empty()){
            dailyLogCommandes << "\n[COMMANDES PASSEES CE JOUR]\n";
            for(auto &cm : commandesDuJour){
                dailyLogCommandes <<"Commande #"<< cm.commandeID 
                                <<" (Client "<< cm.client.id <<") : ";
                for(int r : cm.refProduits){
                    dailyLogCommandes << r <<" ";
                }
                dailyLogCommandes << "\n";
            }
        } else {
            dailyLogCommandes << "\nAucune commande passee ce jour.\n";
        }

        // ---------- VERIFICATION CAPACITE & ASSIGNATION ou REFUS ----------
        for (auto &cm : commandesDuJour) {
            int needed = (int)cm.refProduits.size();
            int freeCapacity = 0;
            for (auto &t : transporteurs) {
                if (t.currentCommandeID == 0 && t.itemsOnBoard == 0 && t.produits.empty()) {
                    freeCapacity += t.capacite;
                }
            }
            if (freeCapacity < needed) {
                dailyLog << "Commande #" << cm.commandeID << " (Client " 
                        << cm.client.id << ") REFUSEE : pas assez de transporteurs.\n";
                continue;
            }

            int nbRest = (int)cm.refProduits.size();
            auto itStart = cm.refProduits.begin();

            for (auto &t : transporteurs) {
                if (nbRest <= 0) break;

                if (t.currentCommandeID == 0 && t.itemsOnBoard == 0 && t.produits.empty()) {
                    int portion = std::min(nbRest, t.capacite);
                    t.refsAttendus.clear();
                    t.refsAttendus.insert(
                        t.refsAttendus.end(),
                        itStart, itStart + portion
                    );

                    t.currentCommandeID = cm.commandeID;
                    t.destination       = cm.client.region;
                    t.itemsOnBoard     = portion; 

                    itStart += portion;
                    nbRest  -= portion;
                }
            }
        }

        // ---------- MOUVEMENTS MANUTENTIONS ----------
        for (auto& m : manutentions) {
            int transferts = 0;

            // etape 1 : Quai de sortie -> Transporteur sortant
            for (auto& t : transporteurs) {
                if (t.currentCommandeID != 0) {
                    int transf = m.transfererStockageToTransporteur(quaiSortie, t, m.capacite);
                    if (transf > 0) {
                        dailyLog << "Manut#" << m.id << " transfere " << transf
                                 << " produits QuaiSortie->Transporteur#" << t.id << "\n";
                        break; 
                    }
                }
            }

            // etape 2 : Convoyeur de sortie -> Quai de sortie
            if (!convoyeursSortie[0].produits.empty()) {
                transferts = m.transfererProduits(convoyeursSortie[0], quaiSortie, m.capacite);
                if (transferts > 0) {
                    dailyLog << "Manut#" << m.id << " transfere " << transferts
                             << " produits ConvSortie[0]->QuaiSortie\n";
                    continue;
                }
            }

            // etape 3 : Entrepôt -> Convoyeur de sortie
            if (!entrepot.produits.empty()) {
                transferts = m.transfererProduits(entrepot, convoyeursSortie[0], m.capacite);
                if (transferts > 0) {
                    dailyLog << "Manut#" << m.id << " transfere " << transferts
                             << " produits Entrepot->ConvSortie[0]\n";
                    continue;
                }
            }

            // etape 4 : Convoyeur d'entree -> Entrepôt
            if (!convoyeursEntree[0].produits.empty()) {
                transferts = m.transfererProduits(convoyeursEntree[0], entrepot, m.capacite);
                if (transferts > 0) {
                    dailyLog << "Manut#" << m.id << " transfere " << transferts
                             << " produits ConvEntree[0]->Entrepot\n";
                    continue;
                }
            }

            // etape 5 : Quai d'entree -> Convoyeur d'entree
            if (!quaiEntree.produits.empty()) {
                transferts = m.transfererProduits(quaiEntree, convoyeursEntree[0], m.capacite);
                if (transferts > 0) {
                    dailyLog << "Manut#" << m.id << " transfere " << transferts
                             << " produits QuaiEntree->ConvEntree[0]\n";
                    continue; 
                }
            }

            // etape 6 : Transporteur -> Quai d'entree
            for (auto& t : transporteurs) {
                if (!t.produits.empty() && t.currentCommandeID == 0) {
                    transferts = m.transfererTransporteurToStockage(t, quaiEntree, m.capacite);
                    if (transferts > 0) {
                        dailyLog << "Manut#" << m.id << " transfere " << transferts
                                 << " produits T#" << t.id << "->QuaiEntree\n";
                        break; // un seul mouvement / jour / manutention
                    }
                }
            }
            if (transferts > 0) continue;
        }

        // ============= VERIFICATION DES COMMANDES PRÊTES A LIVRER =============
        {
            std::map<int, std::vector<Transporteur*>> commandeToTransporteurs;
            for (auto &t : transporteurs) {
                if (t.currentCommandeID != 0) {
                    commandeToTransporteurs[t.currentCommandeID].push_back(&t);
                }
            }

            for (auto &kv : commandeToTransporteurs) {
                int cmdID = kv.first;
                auto &vecT = kv.second;

                bool allReady = true;
                int totalProduitsPourCetteCommande = 0;

                for (auto *pt : vecT) {
                    if ((int)pt->produits.size() != (int)pt->refsAttendus.size()) {
                        allReady = false;
                        break;
                    }

                    std::multiset<int> setRefs;
                    for (auto &pr : pt->produits) {
                        setRefs.insert(pr.reference);
                    }
                    std::multiset<int> setAttendus(pt->refsAttendus.begin(), pt->refsAttendus.end());

                    if (setRefs != setAttendus) {
                        allReady = false;
                        break;
                    }

                    totalProduitsPourCetteCommande += (int)pt->produits.size();
                }

                if (allReady) {
                    auto itCmd = std::find_if(commandesNonLivrees.begin(), commandesNonLivrees.end(),
                        [cmdID](const Commande &c){ return c.commandeID == cmdID; });
                    if (itCmd != commandesNonLivrees.end()) {
                        itCmd->isLivred = true;  
                    }

                    dailyLog << "Commande #" << cmdID << " livree par transporteur(s) ";
                    for (auto *pt : vecT) {
                        dailyLog << "#" << pt->id << " ";
                        pt->produits.clear();          // vide le conteneur
                        pt->currentCommandeID = 0;     // plus de commande
                        pt->itemsOnBoard = 0;
                        pt->refsAttendus.clear();
                        pt->destination = regions[0];  // redevient 'Plateforme'
                    }
                    dailyLog << "\n";

                    totalDelivered += totalProduitsPourCetteCommande;
                }
            }
        }
        dailyLog << dailyLogCommandes.str();

        // ================= AFFICHAGE ==================

        // (1) Nombre produit total genere
        std::cout << "Total produits generes (depuis debut) : " 
                  << totalProductsGenerated << "\n";

        // (2) Nombre produit actuellement stocke
        long long totalInPlatform=0;
        totalInPlatform += quaiEntree.produits.size();
        totalInPlatform += quaiSortie.produits.size();
        for(auto &cv : convoyeursEntree) totalInPlatform += cv.produits.size();
        for(auto &cv : convoyeursSortie) totalInPlatform += cv.produits.size();
        totalInPlatform += entrepot.produits.size();
        for(auto &t : transporteurs){
            if(t.currentCommandeID==0){
                totalInPlatform += t.produits.size();
            }
        }
        std::cout << "Produits actuellement dans la plateforme : "
                  << totalInPlatform << "\n";

        // (3) Nombre produit livre
        std::cout << "Nombre de produits livres : " << totalDelivered << "\n";

        // (4) Resume des transferts du jour
        std::cout << "\n--- Resume des transferts du jour ---\n";
        std::cout << dailyLog.str() << "\n";

        // (5) Commandes aujourd'hui (ce jour + jours precedents)
        std::cout << "\n--- Commandes (auj. + jours precedents) ---\n";
        if(commandesNonLivrees.empty()){
            std::cout<<"Aucune commande.\n";
        } else {
            for(auto &cmd : commandesNonLivrees){
                std::cout << "Cmd#" << cmd.commandeID << " (Client " << cmd.client.id << ")"
                          << " [Livree? " << (cmd.isLivred?"Oui":"Non") << "] : ";
                for(int r: cmd.refProduits) std::cout << r << " ";
                std::cout << "\n";
            }
        }

        // (6) Etat de toutes les manutentions
        std::cout<<"\n--- Etat de TOUTES les manutentions ---\n";
        for(auto &m: manutentions){
            std::cout<<"Manut#"<<m.id<<" (cap="<<m.capacite<<") ";
            if(m.affecteeACommande){
                std::cout<<"[AFFECTEE cmd#"<<m.commandeID<<"]\n";
            } else {
                std::cout<<"[LIBRE]\n";
            }
        }

        // (7) Etat des transporteurs arrivant (destination= Plateforme)
        std::cout<<"\n--- Transporteurs ARRIVANTS (destination=Plateforme) ---\n";
        for(auto &t : transporteurs){
            if(t.destination.id==0){
                std::string prefix = "Transporteur#"+std::to_string(t.id);
                afficherProduits(prefix, t.produits);
            }
        }

        // (8) Etat du Quai d'entree
        {
            std::cout<<"\n--- Quai d'entree ---\n";
            std::string prefix = "Quai Entree (cap="+ std::to_string(quaiEntree.getCapacite()) +")";
            afficherProduits(prefix, quaiEntree.produits);
        }

        // (9) Etat des convoyeurs d'entree
        std::cout << "\n--- Convoyeurs d'Entree ---\n";
        for(size_t i=0; i<convoyeursEntree.size(); i++){
            std::string prefix = "ConvEntree#"+std::to_string(i)
                +" (cap="+std::to_string(convoyeursEntree[i].getCapacite())+")";
            afficherProduits(prefix, convoyeursEntree[i].produits);
        }

        // (10) Etat de l'entrepot
        {
            std::cout<<"\n--- Entrepot ---\n";
            std::string prefix= "Entrepot (cap="+ std::to_string(entrepot.getCapacite())+")";
            afficherProduits(prefix, entrepot.produits);
        }

        // (11) Etat des convoyeurs de sortie
        std::cout << "\n--- Convoyeurs de Sortie ---\n";
        for(size_t i=0; i<convoyeursSortie.size(); i++){
            std::string prefix="ConvSortie#"+std::to_string(i)
                +" (cap="+std::to_string(convoyeursSortie[i].getCapacite())+")";
            afficherProduits(prefix, convoyeursSortie[i].produits);
        }

        // (12) Etat du Quai de sortie
        {
            std::cout<<"\n--- Quaie de sortie ---\n";
            std::string prefix="QuaiSortie (cap="+ std::to_string(quaiSortie.getCapacite())+")";
            afficherProduits(prefix, quaiSortie.produits);
        }

        // (13) Etat des transporteurs ayant une commande
        std::cout<<"\n--- Transporteurs AVEC commande ---\n";
        bool anyCmdTransporter=false;
        for(auto &t : transporteurs){
            if(t.currentCommandeID!=0){
                anyCmdTransporter=true;
                std::cout << "\nTransporteur#"<<t.id<<" -> cmd#"<<t.currentCommandeID
                          <<" - itemsOnBoard="<< t.itemsOnBoard <<"\n";
                std::cout << "--- Produits attendus par le transporteur ---\n";
                // Rechercher la commande dans commandesNonLivrees
                auto it = std::find_if(commandesNonLivrees.begin(), commandesNonLivrees.end(),
                    [&t](const Commande& cmd) { return cmd.commandeID == t.currentCommandeID; });
                if (it != commandesNonLivrees.end()) {
                    t.afficherProduitsAttendus();
                }

                // Afficher le vecteur produits si besoin
                afficherProduits("  -> Produits a bord", t.produits);
            }
        }
        if(!anyCmdTransporter){
            std::cout<<"Aucun transporteur n'a de commande.\n";
        }

        // 14) Avancer d'un jour ?
        std::cout<<"\nAppuyez sur 'n' pour avancer d'un jour, ou 'q' pour quitter : ";
        char ccc;
        std::cin >> ccc;
        if(ccc=='q') break;
        else if(ccc=='n') currentDay++;
        else std::cout<<"Choix invalide.\n";
    }
}

// ------------------------------------------------
//  Méthode d'affichage de produits (ex utilitaire)
// ------------------------------------------------
void Simulation::afficherProduits(const std::string& prefix, const std::vector<Produit>& produits){
    std::cout << prefix << " contient " << produits.size() << " produit(s)\n";
    for(const auto &p : produits){
        std::cout << "   [ID=" << p.id << ", Ref="<< p.reference 
                  << ", Nom=" << p.nom << ", Dest=" << p.destination << "]\n";
    }
}
