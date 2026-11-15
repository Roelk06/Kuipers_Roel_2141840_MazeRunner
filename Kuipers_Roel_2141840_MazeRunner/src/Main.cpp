// name: Main.cpp
#include <iostream>
#include "Game.h"
#include "GameWindow.h"

int main(){
	Game game;

	cout << "1. Load maze from a file" << endl;
	cout << "2. Generate a maze" << endl;
	cout << "Choose either 1 or 2" << endl;

	int choice;
	cin >> choice;

	if(choice == 1){
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

	GameWindow* window = new GameWindow(game);
	window->show();
	return Fl::run();
}

