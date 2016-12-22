// Austin Dudas

#include "Game.h"
#include <string>

using namespace std;

// Set up and start the game 
void Game::startGame() {
    os << "Starting a new game of Othello\n";
    os << Tile::toChar(currentPlayer) << " goes first\n\n";
    while (!board.isFull()) {
        takeTurn();
    }
}

void Game::takeTurn() {
    // Print the board
    board.printWithCoords(os);
    os << '\n' << Tile::toChar(currentPlayer) 
    << "'s turn - Enter a position in [LETTER][NUMBER] format\n";
    // Get the input 
    Position pos = getPositionInput();
    // Play the piece
    board.playPiece(pos.row, pos.col, currentPlayer);
    // Change players
    changePlayers();
}

// change players 
void Game::changePlayers() {
    if (currentPlayer == Tile::BLACK) {
        currentPlayer = Tile::WHITE;
    }
    else {
        currentPlayer = Tile::BLACK;
    }
}

// get position input 
Position Game::getPositionInput() {
    // variable
    string input;
    bool good = false;
    int row = -1, col = -1;
    
    while (!good) {
        good = true;
        os << "POSITION TO PLAY: ";
        getline(cin, input);
        
        // Validate
        // only 2 characters 
        if (input.size() != 2) {
            os << "Invalid input. Must be 2 characters: [LETTER][NUMBER]\n";
            good = false;
        }
        // character 1 
        else if (input[0] < 'A' || input[0] > ('A' + board.getSize() - 1)) {
            os << "Invalid row\n";
            good = false;
        }
        // character 2
        else if (input[1] < '0' || input[1] > ('0' + board.getSize() - 1)) {
            os << "Invalid column\n";
            good = false;
        }
        // check validity with board state 
        else {
            row = int(input[0] - 'A');
            col = int(input[1] - '0');
            good = board.checkValidMove(row, col, currentPlayer);
            if (!good)
                os << "It's invalid for you to play there\n";
        }
    }
    os << '\n';
    Position pos;// = { row, col };
    pos.row = row;
    pos.col = col;
    return pos;   
}