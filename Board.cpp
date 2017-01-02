// Austin Dudas

#include "Board.h"

using namespace std;

// Constructor
Board::Board(bool colors) : size(8) {
    // Adjust board size
    tiles.resize(size);
    for (int i = 0; i < size; ++i) {
        tiles[i].resize(size, Tile(colors));
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
    // Move is normally valid
    if (tiles[r][c].isEmpty() && checkAllDirections(r, c, player))
        return true;
    // Move is valid when no flips are available
    else if (noOtherValidMoves(r, c, player)) {
        return true;
    }
    // Move isn't valid
    return false;
}

// Play a piece 
void Board::playPiece(int r, int c, int player) {
    tiles[r][c].setOccupant(player);
    flipAllDirections(r, c, player);
    --emptySpaces;
}

// Check a direction for flippable tiles 
bool Board::checkDirection(int r, int c, int player,
int rChange, int cChange) {
    
    // Check adjacent in bounds 
    if (r + rChange >= size || r + rChange < 0) return false;
    if (c + cChange >= size || c + cChange < 0) return false;
    
    // Check adjacent tile 
    int occ = tiles[r + rChange][c + cChange].getOccupant();
    if (occ == player || occ == Tile::EMPTY) return false;
    
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

// flip all the tiles in a direction
void Board::flipDirection(int r, int c, int player, int rChange, int cChange) {
    // check the direction to avoid wasting time and errors
    if (checkDirection(r, c, player, rChange, cChange)) {
        // Go that direction 
        for (int i = 1; i < size; ++i) {
            Tile& t = tiles[r + i * rChange][c + i * cChange];
            // Flip if necessary
            if (t.getOccupant() != player)
                t.flip();
            // return if flips are done
            else
                return;
        }
    }
}

// flip all the tiles in every direction where possible
void Board::flipAllDirections(int r, int c, int player) {
    flipDirection(r, c, player, 0, 1);
    flipDirection(r, c, player, 1, 1);
    flipDirection(r, c, player, 1, 0);
    flipDirection(r, c, player, 1, -1);
    flipDirection(r, c, player, 0, -1);
    flipDirection(r, c, player, -1, -1);
    flipDirection(r, c, player, -1, 0);
    flipDirection(r, c, player, -1, 1);
}

// for the case where you can't flip any tiles anywhere
bool Board::noOtherValidMoves(int r, int c, int player) {

    if (!adjacentOccupiedTileExists(r, c)) {
        return false;
    }

    // check the full board for other valid moves (costly AF)
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (tiles[r][c].isEmpty() && !checkAllDirections(r, c, player)) {
                return false;
            }
        }
    }

    return true;
}

// See if there are any adjacent occupied tiles to r c
bool Board::adjacentOccupiedTileExists(int r, int c) {
    // Check all directions
    return (
        checkOccupiedTile(r, c + 1) ||
        checkOccupiedTile(r + 1, c + 1) ||
        checkOccupiedTile(r + 1, c) ||
        checkOccupiedTile(r + 1, c - 1) ||
        checkOccupiedTile(r, c - 1) ||
        checkOccupiedTile(r - 1, c - 1) ||
        checkOccupiedTile(r - 1, c) ||
        checkOccupiedTile(r - 1, c + 1)
    );
}

// Check if tile at r c is in bounds and occupied
bool Board::checkOccupiedTile(int r, int c) {
    // Make sure it's in bounds
    if (r < 0 || r >= size || c < 0 || c >= size)
        return false;
    // Return true if it's not empty
    return (!tiles[r][c].isEmpty());
}

// Count tiles for player
int Board::countTiles(int player) {
    
    int result = 0;
    
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            if (tiles[r][c].getOccupant() == player)
                ++result;
        }
    }

    return result;
}