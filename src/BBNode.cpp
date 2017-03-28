#include "BBNode.hpp"

BBNode::BBNode(DataSched * ptr){
    this->dataPtr = ptr;
    this->currentSolution = vector<int>(ptr->nbItems, -1);
    this->isFixed = vector<bool>(ptr->nbItems, false);
    this->lastDateOfLastFixedPiece = ptr->makespan;

    this->lastPosNonFixed = ptr->nbItems - 1; // - 1 pour éviter les segfault
}

BBNode::BBNode(const BBNode & bbn)  {
    this->dataPtr = bbn.dataPtr;
    this->borneInf = bbn.borneInf;
    this->currentSolution = bbn.currentSolution;
    this->isFixed = bbn.isFixed;
    this->lastDateOfLastFixedPiece = bbn.lastDateOfLastFixedPiece;

    this->lastPosNonFixed = bbn.lastPosNonFixed;
}

void BBNode::Evaluate(){
    cout << __PRETTY_FUNCTION__ << " passage boucle ! " << this->lastDateOfLastFixedPiece << endl;
    int maxi = max(this->lastDateOfLastFixedPiece - this->dataPtr->dueDate.at(currentSolution.at(lastPosNonFixed)), 0);

    this->borneInf += (maxi) * this->dataPtr->penalty.at(currentSolution.at(lastPosNonFixed));
    this->lastDateOfLastFixedPiece = this->lastDateOfLastFixedPiece - this->dataPtr->procTime.at(currentSolution.at(lastPosNonFixed)); // correspond à la dernière date pour la dernière pièce fixé

    --lastPosNonFixed;
}

bool BBNode::isASolution() {
    // si il n'y a plus d'élément à fixé
    if (lastPosNonFixed == 0) {
        return true;
    }
    return false;
}

vector<int> BBNode::getSolution() {
    return this->currentSolution;
}

list<BBNode> BBNode::createChildren(){

    list<BBNode> tmp_list;

    for (unsigned int i = 0; i < isFixed.size(); i++) {
        if (isFixed.at(i) == false) {
            // i can take the piece
            BBNode tmp(*this);
            tmp.currentSolution.at(lastPosNonFixed) = i;
            tmp.Evaluate();
            tmp.isFixed.at(i) = true;
            tmp_list.push_back(tmp);
        }
        else {
            // i cannot take the piece
            // do nothing
        }
    }

    return tmp_list;
}

bool BBNode::operator> (const BBNode & node) const{ // cf les priorityQueue
    return (this->borneInf > node.borneInf);
}



ostream & operator<< (ostream & os, const BBNode & bbn){
    os << "BI : " << bbn.borneInf << endl;
    os << "SOL : < ";
    for (auto it : bbn.currentSolution){
        os << it << " ";
    }
    os << ">" << endl;

    return os;
}
