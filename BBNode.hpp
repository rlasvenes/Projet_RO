#ifndef BBNode_h
#define BBNode_h

#include <iostream>
#include <list>
#include <vector>

#include "DataSched.hpp"

using namespace std;

class BBNode{
    public :
        DataSched * dataPtr;        /* Pointer on the instance data */

        int borneInf;
        int numberOfElementsLeft;

        vector<int> currentSolution;
        vector<int> piecesRef;


        // .....


        BBNode(DataSched * ptr);    /* constructor for the root node */
        BBNode(const BBNode & bbn); /* copy contructor, used to create children */

        void Evaluate();
        list<BBNode> createChildren();
        bool isASolution();
        vector<int> getSolution();
        void computeLowerBound(bool isLastSolution);
        void computeCurrentSolution(bool isLastSolution);
        bool operator> (const BBNode & node) const;

};

ostream & operator<< (ostream & of, const BBNode & bbn);

#endif
