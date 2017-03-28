#ifndef BBNode_h
#define BBNode_h

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#include "DataSched.hpp"

using namespace std;

class BBNode{
    public :
        DataSched * dataPtr;        /* Pointer on the instance data */

        int borneInf;
        int lastPosNonFixed;
        int lastDateOfLastFixedPiece;

        vector<int> currentSolution;
        vector<bool> isFixed;


        // .....


        BBNode(DataSched * ptr);    /* constructor for the root node */
        BBNode(const BBNode & bbn); /* copy contructor, used to create children */
        void Evaluate();
        bool isASolution();
        vector<int> getSolution();
        list<BBNode> createChildren();
        bool operator> (const BBNode & node) const;

};

ostream & operator<< (ostream & of, const BBNode & bbn);

#endif
