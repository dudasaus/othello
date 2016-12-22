// Austin Dudas

#include <iostream>

using namespace std;

class Tile {
public:
    static const int EMPTY = 0, BLACK = 1, WHITE = 2;
    
private:
    int occupant;
    
public:
    // Default constructor
    Tile() : occupant(EMPTY) {};
    // Another constructor 
    Tile(int inOccupant) : occupant(inOccupant) {};
    
    // toChar
    char toChar() {
        const char tileReps[] = {'.', 'X', 'O'};
        return tileReps[occupant];
    }
    static char toChar(int c) {
        const char tileReps[] = {'.', 'X', 'O'};
        return tileReps[c];
    }
    
    // isEmpty()
    bool isEmpty() {
        return (occupant == EMPTY);
    }
    
    // Getters
    int getOccupant() {
        return occupant;
    }
    
    // Setters
    void setOccupant(int inOccupant) {
        occupant = inOccupant;
    }
};

inline ostream& operator<<(ostream& os, Tile& tile) {
    os << tile.toChar();
    return os;
}