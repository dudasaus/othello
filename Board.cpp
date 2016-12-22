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
    
    // Set empty spaces
    emptySpaces = (size * size) - 4;
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
    for (int r = -1; r < size; ++r) {
        // Print the letter of the row
        if (r > - 1) 
            os << char('A' + r) << ' ';
        else os << ' ' << ' ';
        
        for (int c = 0; c < size; ++c) {
            if (r > -1)
                os << tiles[r][c];
            else
                os << c;
        }
        os << '\n';
    }
}

// is full 
bool Board::isFull() {
    return (emptySpaces == 0);
}

// Check for valid move 
bool Board::checkValidMove(int r, int c, int player) {
    return (tiles[r][c].isEmpty() && checkAllDirections(r, c, player));
}

// Play a piece 
void Board::playPiece(int r, int c, int player) {
    tiles[r][c].setOccupant(player);
    --emptySpaces;
}

// Check a direction for flippable tiles 
bool Board::checkDirection(int r, int c, int player,
int rChange, int cChange) {
    //cerr << "Checking " << rChange << ' ' << cChange << '\n';
    
    // Check adjacent in bounds 
    if (r + rChange >= size || r + rChange < 0) return false;
    if (c + cChange >= size || c + cChange < 0) return false;
    
    // Check adjacent tile 
    int occ = tiles[r + rChange][c + cChange].getOccupant();
    if (occ == player || occ == Tile::EMPTY) return false;
    
    // get the other player 
    int other = (player == Tile::WHITE) ? Tile::BLACK : Tile::WHITE;
    
    // Continue checking down the line 
    for (int i = 2; i < size; ++i) {
        int rCheck = r + i * rChange;
        int cCheck = c + i * cChange;
        // check bounds 
        if (rCheck < 0 || rCheck >= size) return false;
        if (cCheck < 0 || cCheck >= size) return false;
        
        // get tile 
        occ = tiles[rCheck][cCheck].getOccupant();
        
        // check if empty 
        if (occ == Tile::EMPTY) return false;
        // check if other 
        if (occ == player) return true;
    }
    
    // Return false 
    return false;
}

// check all directions 
bool Board::checkAllDirections(int r, int c, int player) {
    return (
        checkDirection(r, c, player, 0, 1) ||
        checkDirection(r, c, player, 1, 1) ||
        checkDirection(r, c, player, 1, 0) ||
        checkDirection(r, c, player, 1, -1) ||
        checkDirection(r, c, player, 0, -1) ||
        checkDirection(r, c, player, -1, -1) ||
        checkDirection(r, c, player, -1, 0) ||
        checkDirection(r, c, player, -1, 1)
    );
}