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
		this->color(fl_rgb_color(60, 60, 60));
	}else if(symbol == 'P'){
		this->color(fl_rgb_color(40, 90, 170));
		this->labelcolor(FL_WHITE);
		this->label("P");
	}else if(symbol == 'T'){
		this->color(fl_rgb_color(240, 200, 60));
		this->label("T");
	}else if(symbol == 'E'){
		this->color(fl_rgb_color(200, 50, 50));
		this->label("E");
	}else if(symbol == 'X'){
		this->color(fl_rgb_color(46, 139, 87));
		this->label("X");
	}else{
		this->color(FL_WHITE);
	}
	this->redraw();
}

