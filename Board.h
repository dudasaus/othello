// Austin Dudas

#include "Tile.h"
#include <vector>

using namespace std;

class Board {
private:
    int size;
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
    
    bool checkValidMove(int r, int c, int player);
};