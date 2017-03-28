#include <iostream>
#include <limits>
#include <vector>
#include <queue>

#include "BBNode.hpp"
#include "DataSched.hpp"

#define BORNE_INF_DEFAULT_VALUE 0

using namespace std;

// va permettre de trouver la dernière valeur non fixée
// grace à une différence de vector
int checkSolution(DataSched d, vector<int> bestSolution) {
    vector<int> copy = vector<int>(d.nbItems);
    for (unsigned int i = 0; i < copy.size(); i++) {
        copy.at(i) = i;
    }

    vector<int> res(d.nbItems);
    std::sort(bestSolution.begin(), bestSolution.end()); // <0,1,2,3,4,...,n>
    auto it = set_difference(copy.begin(), copy.end(), bestSolution.begin(), bestSolution.end(),
                             res.begin());
    res.resize(it - res.begin());

    return res.front();
}

int main (int argc, char** argv){
    DataSched data;
    int bestUpperBound = numeric_limits<int>::max();
    vector<int> bestSolution;

    if (argc > 1){
        data.readDataFile(argv[1]);
    } else {
        char * filename = new char[256];
        cout << "Entrez le nom du fichier de données" << endl;
        cin >> filename;
        data.readDataFile(filename);
        delete [] filename;
    }

    list<BBNode> listNodes;

    /*
     *
     * Créer parent
     * ajouter parent à listeATraiter
     * while !list.empty()
     *  prendre et supprimer un noeud de la liste
     *  si borneInf < meilleure sol trouvé, then
     *      creer enfant du noeud (copie du parent)
     *      for each children, do
     *          calculer borne inf de l'enfant
     *          si borne inf < meilleure sol, then
     *              si enfant est solution et que meilleure que sol trouvé, then
     *                  meilleure sol = sol trouvé
     *              sinon
     *                  ajouter enfant à liste des noeuds à traiter
     *
     *
     *
    */

    BBNode parent(&data); // racine de l'arbre
    parent.borneInf = BORNE_INF_DEFAULT_VALUE; // on met la borne inf du parent à 0

    listNodes.push_back(parent);

    int nb_noeuds = 0;
    while (!listNodes.empty()) {
        BBNode currentNode = listNodes.back();
        listNodes.pop_back();

        // si on trouve une borne intéréssante à parcourir (plus petite borne inf)
        if (currentNode.borneInf < bestUpperBound) {
            list<BBNode> childrens = currentNode.createChildren();
            nb_noeuds += childrens.size();

            for (BBNode n : childrens) {
                cout << n << endl;
                cout << "BORNE SUP = " << bestUpperBound << endl;
                if (n.borneInf < bestUpperBound) {
                    if (n.isASolution()) { // si toutes les pièces sont fixées
                        bestSolution = n.getSolution();
                        bestUpperBound = n.borneInf; // on actualise la borne sup
                    }
                    else {
                        listNodes.push_back(n); // on ajoute notre noeud à la liste de traitement
                    }
                }
            }
        }
    }

    // ...

    bestSolution.at(0) = checkSolution(data, bestSolution); // c'est TOUJOURS la première pièce dans le vecteur qui n'était jamais traité, donc at(0)

    cout << "Solution value : " << bestUpperBound << endl;
    cout << "Optimal solution : " << endl;
    cout << "<";
    for (vector<int>::iterator it = bestSolution.begin();
         it != bestSolution.end(); it++){
        cout << *it << ",";
    }
    cout << ">" << endl;

    cout << "========================================================" << endl;
    cout << "Noeuds crées : " << nb_noeuds << endl;
    cout << "Borne supérieure : " << bestUpperBound << endl;
    cout << "========================================================" << endl;

    return 0;
}
