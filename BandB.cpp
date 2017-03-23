#include <iostream>
#include <limits>
#include <vector>
#include <queue>

#include "BBNode.hpp"
#include "DataSched.hpp"

#define BORNE_INF_DEFAULT_VALUE 0

using namespace std;

void checkDataAfterReading(DataSched d) {
    cout << "STARTING TO CHECK DATA..." << endl;

    for (auto it : d.dueDate) {
        cout << "DUE DATE : " << it << endl;
    }

    for (auto it : d.penalty) {
        cout << "PENALTY : " << it << endl;
    }

    for (auto it : d.procTime) {
        cout << "PROC TIME : " << it << endl;
    }

    cout << "FINISH TO CHECK DATA." << endl;
}

vector<int> buildVectorOfPieces(DataSched d) {
    vector<int> v(d.nbItems);

    for (int i = 0; i < d.nbItems; i++) {
        v.at(i) = i + 1;
    }
    return v;
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

    checkDataAfterReading(data);
    vector<int> pieces = buildVectorOfPieces(data); // vecteur de pièces ex: <1,2,3,4,...,n> où n est le nb de pièces différentes

    BBNode parent(&data);
    parent.piecesRef = pieces;

    parent.borneInf = BORNE_INF_DEFAULT_VALUE; // on met la borne inf du parent à 0
    parent.numberOfElementsLeft = data.nbItems; // au début, y'a autant d'éléments à traiter que de pièces
    parent.currentSolution = vector<int>(data.nbItems, 0); // notre solution (ordre de passage des pièces) = <0,0,0,0> avec n = 4

    listNodes.push_back(parent); // on ajoute le parent à la liste des sommets à traiter

    while (!listNodes.empty()) { // tant qu'il y a des noeuds à traiter, on process
        cout << "------------ AVANCEMENT ------------\n" <<
                "taille liste : " << listNodes.size() << "\n" <<
                "bestSolution.size() : " << bestSolution.size() << "\n" <<
                "bestUpperBound : " << bestUpperBound << "\n" <<
                "------------------------------------\n" << endl;

        BBNode currentNode = listNodes.front(); // on prend le premier noeud de la liste...
        listNodes.pop_front(); // ... et on l'enlève aussitôt après

        if (currentNode.borneInf < bestUpperBound) {
            list<BBNode> childrens = currentNode.createChildren(); // à ce moment là, la BI de chaque enfant est définie
            //bestUpperBound = currentNode.borneInf;

            // actualiser notre noeud (elements restants, ...)
            for (BBNode n : childrens) {
                cout << n << endl;
                n.Evaluate();
                if (n.borneInf < bestUpperBound) {
                    // faire quelque chose
                    if (n.isASolution()) { // je ne pense pas que çe soit bon, car une solution n'est pas forcément LA meilleure solution ==> faire un checkSolution(solution)
                        bestSolution = n.getSolution();
                    }
                    else {
                        listNodes.push_back(n);
                    }
                }
            }
        }
    }



    // ...







    cout << "Solution value : " << bestUpperBound << endl;
    cout << "Optimal solution : " << endl;
    cout << "<";
    for (vector<int>::iterator it = bestSolution.begin();
         it != bestSolution.end(); it++){
        cout << *it << ",";
    }
    cout << ">" << endl;

    return 0;
}
