// name: Main.cpp
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include "Game.h"
#include "GameWindow.h"
#include "cstdlib"
#include "ctime"


int main(){
	srand(time(0));

	Game game;
	    try {
	        game.load("maze.txt");
	    } catch (string& message) {
	        cerr << "Invalid maze: " << message << endl;
	        return 1;
	    }

	    GameWindow* window = new GameWindow(game);
	    window->show();
	    return Fl::run();
}

