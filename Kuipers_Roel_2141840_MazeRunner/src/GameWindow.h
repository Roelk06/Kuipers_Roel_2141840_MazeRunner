#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <FL/Fl_Window.h>
#include "AI.h"
#include "Grid.h"
#include <fstream>

class GameWindow: public Fl_Window{
	private:
		Game& game;
		Grid *grid;
		AI ai;
		bool aiMode;
		Fl_Box *status;
		Fl_Box *message;
		Fl_Box *summary;
		void updateStatus();
	public:
		GameWindow(Game& game, bool aiMode = false);
		int handle(int event);
		void showSummary();
		static void aiTimerCallback(void* userdata);
		void stepAI();

};

#endif // GAMEWINDOW_H_
