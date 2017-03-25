#include "PiecesFactory.h"

std::vector<int> PiecesFactory::piecesRef;

PiecesFactory::PiecesFactory()
{
}


void PiecesFactory::refill(int nbPieces) {
    piecesRef = std::vector<int>(nbPieces);
    fill(nbPieces);
}

void PiecesFactory::refill(int nbPieces, std::vector<int> usedPieces) {

}

void PiecesFactory::fill(int nbPieces) {
    for (int i = 0; i < nbPieces; i++) {
        piecesRef.at(i) = i + 1;
    }
}

void PiecesFactory::fill(int nbPieces, std::vector<int> usedPieces) {
    piecesRef = std::vector<int>(nbPieces);

    for (int i = 0; i < nbPieces; i++) {
        piecesRef.at(i) = i + 1;
    }

    std::sort(usedPieces.begin(), usedPieces.end());

    auto it = std::set_difference(piecesRef.begin(), piecesRef.end(), usedPieces.begin(), usedPieces.end(),
                                  piecesRef.begin());
    piecesRef.resize(it - piecesRef.begin());
}
