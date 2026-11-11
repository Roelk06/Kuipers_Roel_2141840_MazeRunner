#ifndef GRID_H_
#define GRID_H_

#include <FL/Fl_Box.H>
#include "Block.h"
#include "Game.h"

const int G_SIZE = 20;
const int GRID_SIZE = G_SIZE*BLOCK_SIZE;

class Grid : public Fl_Box{
	private:
		Block* blocks[SIZE][SIZE];
		void createGrid(const Game& game);
	public:
		Grid(int x, int y, const Game& game);
		void update(const Game& game);
};

#endif // GRID_H_
