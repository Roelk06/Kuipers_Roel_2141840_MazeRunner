#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <queue>
#include <cstdlib>
#include <cmath>
#include "Position.h"
using namespace std;


const int SIZE = 20;
const int NUM_TREASURES = 5;
const int NUM_ENEMIES = 3;

class Maze{
	private:
		char grid[SIZE][SIZE];
		Position playerStart;
		Position enemyStarts[NUM_ENEMIES];
		void validate();
		vector<Position> collectReachableCells(Position start);
		int getDistance(Position a, Position b);
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

