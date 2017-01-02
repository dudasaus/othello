// Austin Dudas

#ifndef TILE_H
#define TILE_H 

#include <iostream>

using namespace std;

class Tile {
public:
    static const int EMPTY = 0, BLACK = 1, WHITE = 2;
    
private:
    int occupant;
    bool colors = true;
    
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
    
    // toString
    string toString() {
        if (colors) {
            const string tileReps[] = {"EMPTY","BLACK","WHITE"};
            return tileReps[occupant];
        }
        else 
            return string(1, toChar());
    }
    static string toString(bool colors, int c) {
        if (colors) {
            const string tileReps[] = {"EMPTY","BLACK","WHITE"};
            return tileReps[c];
        }
        else
            return string(1, toChar(c));
    }
    
    // isEmpty()
    bool isEmpty() {
        return (occupant == EMPTY);
    }

    // flip 
    void flip() {
        occupant = (occupant == WHITE) ? BLACK : WHITE;
    }
    
    // Getters
    int getOccupant() {
        return occupant;
    }
    
    // Setters
    void setOccupant(int inOccupant) {
        occupant = inOccupant;
    }
    void setColors(bool inColors) {
        colors = inColors;
    }
};

inline ostream& operator<<(ostream& os, Tile& tile) {
    
    const string output[] = {
        "\x1b[42m\x1b[90m*\x1b[0m",
        "\x1b[42m\x1b[30mO\x1b[0m",
        "\x1b[42m\x1b[97mO\x1b[0m"
    };
    
    const char outputColorless[] = {
        '.',
        'X',
        'O'
    };
    
    if (true)
        os << output[tile.getOccupant()];
    else
        os << outputColorless[tile.getOccupant()];
    
    return os;
}

#endif