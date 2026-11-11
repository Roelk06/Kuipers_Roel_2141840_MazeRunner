#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl_Window.h>
#include "Grid.h"
#include <fstream>

class GameWindow: public Fl_Window{
	private:
		Game& game;
		Grid *grid;
		Fl_Box *status;
		Fl_Box *message;
		Fl_Box *summary;
		void updateStatus();
	public:
		GameWindow(Game& game);
		int handle(int event);
		void showSummary();
};

#endif // GAMEWINDOW_H_
