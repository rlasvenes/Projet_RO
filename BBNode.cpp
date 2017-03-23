#include "BBNode.hpp"

BBNode::BBNode(DataSched * ptr){
    this->dataPtr = ptr;
    this->currentSolution = vector<int>(ptr->nbItems, 0); // on met le vecteur solution à nulle
}

BBNode::BBNode(const BBNode & bbn)  {
    this->dataPtr = bbn.dataPtr;

    this->borneInf = bbn.borneInf;
    this->numberOfElementsLeft = bbn.numberOfElementsLeft;
    this->currentSolution = bbn.currentSolution;
    this->piecesRef = bbn.piecesRef;
}

void BBNode::Evaluate() {

    if (this->numberOfElementsLeft - 1 > 0) { // dans le cas ou numberOfElementsLeft - 1 serait négatif (0 - 1)
        cout << __PRETTY_FUNCTION__ << " --> elements left : " <<  numberOfElementsLeft << endl;
        currentSolution.at(this->numberOfElementsLeft - 1) = piecesRef.at(0);
        borneInf = (this->dataPtr->makespan - this->dataPtr->dueDate.at(numberOfElementsLeft - 1)) * this->dataPtr->penalty.at(numberOfElementsLeft - 1);
    }
    else {
        currentSolution.at(this->numberOfElementsLeft - 1) = piecesRef.at(0);
    }

    --numberOfElementsLeft;
    piecesRef.erase(piecesRef.begin());
}

list<BBNode> BBNode::createChildren() {

    list<BBNode> tmp_list;

    for (int i = 0; i < this->numberOfElementsLeft; i++) {
        BBNode tmp(*this);
        tmp.Evaluate();
        tmp_list.push_back(tmp);
    }

    return tmp_list;
}

bool BBNode::isASolution() {
    // ou bien: if (this->currentSolution.size() == this->dataPtr->nbItems) // donc vecteur rempli
    if (numberOfElementsLeft == 0) {
        return true;
    }
    return false;
}

vector<int> BBNode::getSolution() {
    return this->currentSolution;
}

bool BBNode::operator> (const BBNode & node) const{
    return (this->borneInf > node.borneInf);
}



ostream & operator<< (ostream & os, const BBNode & bbn){
    os << "BI : " << bbn.borneInf << endl;
    os << "SOL : < ";
    for (auto it : bbn.currentSolution){
        os << it << " ";
    }
    os << ">" << endl;

    os << "PIECES : < ";
    for (auto it : bbn.piecesRef){
        os << it << " ";
    }
    os << ">" << endl;
    return os;
}
