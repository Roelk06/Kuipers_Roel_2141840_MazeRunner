// name: Block.cpp
#include "Block.h"

Block::Block(int x, int y, char symbol): Fl_Box(x, y, BLOCK_SIZE, BLOCK_SIZE){
	this->box(FL_FLAT_BOX);
	setSymbol(symbol);
}

void Block::setSymbol(char symbol){
	this->symbol = symbol;
	this->label("");
	this->labelcolor(FL_BLACK);

	if(symbol == '#'){
		this->color(fl_rgb_color(40, 35, 55));
	}else if(symbol == 'P'){
		this->color(fl_rgb_color(0, 255, 255));
		this->label("P");
	}else if(symbol == 'T'){
		this->color(fl_rgb_color(255, 255, 0));
		this->label("T");
	}else if(symbol == 'E'){
		this->color(fl_rgb_color(255, 50, 100));
		this->label("E");
	}else if(symbol == 'X'){
		this->color(fl_rgb_color(50, 255, 100));
		this->label("X");
	}else{
		this->color(FL_WHITE);
	}
	this->redraw();
}

