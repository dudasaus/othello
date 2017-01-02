// Austin Dudas

#include "Game.h"
#include <getopt.h>

using namespace std;

int main(int argc, char** argv) {
    
    // Welcome message
    cout << "Welcome to Othello!\nUse the --nocolors option (or -n)"
         << " if the colored output isn't working.\n\n";
    
    // Colors variable
    bool colors = true;
    
    // Arguments for getopt_long 
    int opt_index = 0;
    option long_options[] = {
        {"nocolors", no_argument, 0, 'n'}
    };
    
    // Get arguments from command line 
    char c;
    while ((c = (char)getopt_long(argc, argv, "n",
        long_options, &opt_index)) != -1) {
        
        switch (c) {
            // --nocolors -n
            case 'n':
            {
                // turn off colors 
                colors = false;
                break;
            }
            // Default
            default:
                cerr << "Unrecognized argument" << endl;
                exit(1);
                break;
        }
    }
    
    Game game(colors);
    game.startGame();
    
    return 0;
}