#ifndef PIECESFACTORY_H
#define PIECESFACTORY_H

#include <iostream>
#include <vector>
#include <algorithm>

class PiecesFactory
{
    public:
        PiecesFactory();

    public :
        static std::vector<int> piecesRef;
        static void refill(int nbPieces);
        static void refill(int nbPieces, std::vector<int> usedPieces);

    public :
        static void fill(int nbPieces);
        static void fill(int nbPieces, std::vector<int> usedPieces);
};

#endif // PIECESFACTORY_H
