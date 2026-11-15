#ifndef MAZE_H_
#define MAZE_H_

#include <fstream>
#include <vector>
#include <random>
#include "Position.h"
using namespace std;


#include <iostream>

const int SIZE = 20;
const int NUM_TREASURES = 5;
const int NUM_ENEMIES = 3;

class Maze{
	private:
		char grid[SIZE][SIZE];
		Position playerStart;
		Position enemyStarts[NUM_ENEMIES];
		void validate();
		void carvePaths(int r , int c);
	public:
		Maze();
		void load(const string& filename);
		void generate();
		void print() const;
		Position getPlayerStart() const;
		Position getEnemyStart(int index);
		char getSymbol(int row, int col) const;
		bool isInside(Position position);
		bool isWall(Position position);
		bool isTreasure(Position position);
		void removeTreasure(Position position);
		bool isExit(Position position);
		int countTreasures();
};

#endif // MAZE_H_

