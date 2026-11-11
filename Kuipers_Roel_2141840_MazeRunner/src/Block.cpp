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
		this->color(fl_rgb_color(25, 25, 25));
	}else if(symbol == 'P'){
		this->color(fl_rgb_color(140, 140, 140));
		this->labelcolor(FL_WHITE);
		this->label("P");
	}else if(symbol == 'T'){
		this->color(fl_rgb_color(248, 248, 255));
		this->label("S");
	}else if(symbol == 'E'){
		this->color(fl_rgb_color(180, 20, 20));
		this->labelcolor(FL_WHITE);
		this->label("I");
	}else if(symbol == 'X'){
		this->color(fl_rgb_color(220, 90, 20));
		this->labelcolor(FL_WHITE);
		this->label("B");
	}else{
		this->color(fl_rgb_color(40, 40, 45));
	}
	this->redraw();
}

