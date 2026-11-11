// name: Grid.cpp
#include "Grid.h"

Grid::Grid(int x, int y, const Game& game): Fl_Box(x, y, GRID_SIZE, GRID_SIZE) {
    this->box(FL_FLAT_BOX);
    this->color(FL_GRAY);
    createGrid(game);
}

void Grid::createGrid(const Game& game) {
    for (int row=0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            int blockX = x() + col * BLOCK_SIZE;
            int blockY = y() + row * BLOCK_SIZE;
            blocks[row][col] = new Block(blockX, blockY, game.getSymbol(row, col));
            blocks[row][col]->show();
        }
    }
}

void Grid::update(const Game& game){
	for (int row=0; row < SIZE; row++){
		for (int col=0; col < SIZE; col++){
			blocks[row][col]->setSymbol(game.getSymbol(row, col));

		}
	}
}
