all: Tile.h Board.h Board.cpp main.cpp Game.h Game.cpp
	g++ -std=c++14 -Wall -Werror -pedantic -O3 $^ -o othello

clean:
	rm -f othello othello.exe
