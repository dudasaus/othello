// Austin Dudas

#ifndef GAME_H
#define GAME_H 

#include "Board.h"

using namespace std;

struct Position;

class Game {
private:
    Board board;
    int currentPlayer;
    ostream& os = cout;
    bool colors = true;
    
public:
    // Constructor
    Game() : currentPlayer(Tile::BLACK) {};
    
    // start game
    void startGame();
    
    // do a turn
    void takeTurn();
    
    // change players 
    void changePlayers();
    
    // get Position intput
    Position getPositionInput();
    
    
};

struct Position {
    int row = 0;
    int col = 0;
};

#endif