// name: GameWindow.cpp
#include "GameWindow.h"

GameWindow::GameWindow(Game& game): Fl_Window(100, 100, 640, 680, "MazeRunner"), game(game){
	grid = new Grid(20, 20, game);
	status = new Fl_Box(20, 630, GRID_SIZE, 35);
	status->labelfont(FL_BOLD);
	message = new Fl_Box(20, 660, GRID_SIZE, 35);
	summary = new Fl_Box(140, 170, 360, 300);
	summary->box(FL_BORDER_BOX);
	summary->color(FL_WHITE);
	summary->labelsize(18);
	summary->hide();
	end();
}

void GameWindow::updateStatus(){
	const Player& player = game.getPlayer();
	string text = "Score: " + to_string(player.getScore())
                        + "     Lives: " + to_string(player.getLives())
                        + "     Treasures: " + to_string(player.getTreasuresCollected())
                        + "/" + to_string(NUM_TREASURES);
	status->copy_label(text.c_str());

	if(game.isOver()){
		message->copy_label("GAME OVER!");
	}else if(game.getMessage() != ""){
		message->copy_label(game.getMessage().c_str());
	}else{
		 message->copy_label("Move with WASD");
	}
}

void GameWindow::showSummary(){
	Player& player = game.getPlayer();
	string result = "LOSE";
	if(game.hasWon()){
		result = "WIN";
	}
	string text = "GAME OVER\n\nMode: Human\nResult: " + result
			+ "\n\nScore: " + to_string(player.getScore())
			+ "\nTreasures collected: " + to_string(player.getTreasuresCollected()) + " /5"
			+ "\nLives remaining" + to_string(player.getLives())
			+ "\nTurns: " + to_string(game.getTurns());
	summary->copy_label(text.c_str());
	summary->show();

	ofstream file("last_run.txt");
	if(file){
		game.writeSummary(file, "Human");
	}
}

int GameWindow::handle(int event){
	if(event == FL_KEYDOWN){
		int key = Fl::event_key();
		if(key == 'w' || key == 'a' || key == 's' || key == 'd'){
			if(!game.isOver()){
				game.playTurn(key);
				grid->update(game);
				updateStatus();
			}
			if(game.isOver()){
				showSummary();
			}
			return 1;
		}
	}
	return Fl_Window::handle(event);
}

