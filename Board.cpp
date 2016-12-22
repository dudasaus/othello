// Austin Dudas

#include "Board.h"

using namespace std;

// Constructor
Board::Board() : size(8) {
    // Adjust board size
    tiles.resize(size);
    for (int i = 0; i < size; ++i) {
        tiles[i].resize(size);
    }
    
    // Set starter tiles 
    int pos = (size / 2) - 1;
    tiles[pos][pos].setOccupant(Tile::BLACK);
    tiles[pos + 1][pos + 1].setOccupant(Tile::BLACK);
    tiles[pos + 1][pos].setOccupant(Tile::WHITE);
    tiles[pos][pos + 1].setOccupant(Tile::WHITE);
}

// Print
void Board::print(ostream& os) {
    for (int c = 0; c < size; ++c) {
        for (int r = 0; r < size; ++r) {
            os << tiles[r][c];
        }
        os << '\n';
    }
}

// Print
void Board::printWithCoords(ostream& os) {
    for (int c = -1; c < size; ++c) {
        // Print the letter of the row
        if (c > - 1) 
            os << char('A' + c) << ' ';
        else os << ' ' << ' ';
        
        for (int r = 0; r < size; ++r) {
            if (c > -1)
                os << tiles[r][c];
            else
                os << r;
        }
        os << '\n';
    }
}

bool Board::checkValidMove(int r, int c, int player) {
    if (player != 1 && player != 2) return false;
    return (tiles[r][c].isEmpty());
}