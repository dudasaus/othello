// Austin Dudas

#include "Tile.h"
#include <vector>

using namespace std;

class Board {
private:
    int size;
    int emptySpaces;
    vector<vector<Tile> > tiles;
    
public:
    // Constructors
    Board();
    
    // Getters
    int getSize() {
        return size;
    }
    
    // Print
    void print(ostream& os);
    void printWithCoords(ostream& os);
    
    // check is the board is full
    bool isFull();
    
    // Check directions to help valid moves
    bool checkDirection(int r, int c, int player, int rChange, int cChange);
    bool checkAllDirections(int r, int c, int player);
    
    // check for a valid move 
    bool checkValidMove(int r, int c, int player);
    
    // play a piece
    void playPiece(int r, int c, int player);

    // flip directions when playing a piece
    void flipDirection(int r, int c, int player, int rChange, int cChange);
    void flipAllDirections(int r, int c, int player);

    // for the case where you can't flip any tiles
    bool noOtherValidMoves(int r, int c, int player);
    
    // checks to see if any adjacent occupied tiles exists
    bool adjacentOccupiedTileExists(int r, int c);
    bool checkOccupiedTile(int r, int c);

    // Count tiles
    int countTiles(int player);

};