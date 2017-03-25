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
        computeCurrentSolution(false);
        computeLowerBound(false);
    }
    else {
        computeCurrentSolution(true); // true for last element
        computeLowerBound(true);
    }

    --numberOfElementsLeft;
    piecesRef.erase(piecesRef.begin());
}

list<BBNode> BBNode::createChildren() {

    list<BBNode> tmp_list;

    for (int i = 0; i < this->numberOfElementsLeft; i++) {
        BBNode tmp(*this);
        //tmp.Evaluate();
        tmp.currentPiece = piecesRef.front();
        piecesRef.erase(piecesRef.begin());
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

void BBNode::computeLowerBound(bool isLastSolution) {
    if (isLastSolution) {
        borneInf = (this->dataPtr->makespan - this->dataPtr->dueDate.at(numberOfElementsLeft)) * this->dataPtr->penalty.at(numberOfElementsLeft);
    }
    else {
        borneInf = (this->dataPtr->makespan - this->dataPtr->dueDate.at(numberOfElementsLeft - 1)) * this->dataPtr->penalty.at(numberOfElementsLeft - 1);
    }
}

void BBNode::computeCurrentSolution(bool isLastSolution) {
    if (isLastSolution) {
        currentSolution.at(this->numberOfElementsLeft) = piecesRef.at(0);
    }
    else {
        currentSolution.at(this->numberOfElementsLeft - 1) = piecesRef.at(0);
    }
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
