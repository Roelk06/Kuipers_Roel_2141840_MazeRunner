#ifndef BLOCK_H_
#define BLOCK_H_

#include <FL/Fl_Box.H>

const int BLOCK_SIZE = 30;

class Block: public Fl_Box{
	private:
		char symbol;
	public:
		Block(int x, int y, char symbol);
		void setSymbol(char symbol);
};

#endif // BLOCK_H_
