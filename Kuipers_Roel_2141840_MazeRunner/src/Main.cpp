// name: Main.cpp
#include <iostream>
#include "Game.h"
#include "GameWindow.h"
#include <ctime>
#include <cstdlib>

int main(){
	srand(time(0));
	Game game;

	cout << "1. Load maze from a file" << endl;
	cout << "2. Generate a maze" << endl;
	cout << "Choose either 1 or 2" << endl;

	int mazeChoice;
	cin >> mazeChoice;



	if(mazeChoice == 1){
		string filename;
		cout << "Enter filename:" << endl;
		cin >> filename;
		try{
			game.load(filename);
		}catch(const string& message){
			cerr << "Invalid maze: " << message << endl;
			return 1;
		}
	}else{
		cout << "Generating a maze..." << endl;
		game.generate();
	}

	cout << "1. Human mode" << endl;
	cout << "2. AI mode" << endl;
	cout << "Choose either 1 or 2" << endl;

	int modeChoice;
	cin >> modeChoice;
	bool aiMode = (modeChoice == 2);

	GameWindow* window = new GameWindow(game, aiMode);
	window->show();
	return Fl::run();
}

