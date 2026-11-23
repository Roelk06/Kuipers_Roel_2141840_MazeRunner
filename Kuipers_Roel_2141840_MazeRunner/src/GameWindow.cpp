// name: GameWindow.cpp
#include "GameWindow.h"

GameWindow::GameWindow(Game& game, bool aiMode): Fl_Window(100, 100, 640, 710, "MazeRunner"), game(game), aiMode(aiMode){
	grid = new Grid(20, 20, game);
	status = new Fl_Box(20, 630, GRID_SIZE, 35);
	status->labelfont(FL_BOLD);
	message = new Fl_Box(20, 660, GRID_SIZE, 35);
	summary = new Fl_Box(140, 170, 360, 300);
	summary->box(FL_BORDER_BOX);
	summary->color(fl_rgb_color(30, 30, 30));
	summary->labelsize(18);
	summary->hide();
	end();
	updateStatus();

	if(aiMode){
		Fl::add_timeout(0.15, aiTimerCallback, this);
	}
}

void GameWindow::aiTimerCallback(void* userdata){
	GameWindow* window = static_cast<GameWindow*>(userdata);
	window->stepAI();
}

void GameWindow::stepAI(){
	if(game.isOver()){
		return;
	}

	char move = ai.getNextMove(game);
	game.playTurn(move);
	grid->update(game);
	updateStatus();

	if(game.isOver()){
		showSummary();
	}else{
		Fl::repeat_timeout(0.15, aiTimerCallback, this);
	}
}

void GameWindow::updateStatus(){
	const Player& player = game.getPlayer();
	string text = "Score: " + to_string(player.getScore())
                        + "     Lives: " + to_string(player.getLives())
                        + "     Treasure: " + to_string(player.getTreasuresCollected())
                        + "/" + to_string(NUM_TREASURES);
	status->copy_label(text.c_str());

	if(game.isOver()){
		message->copy_label("GAME OVER!");
	}else if(game.getMessage() != ""){
		message->copy_label(game.getMessage().c_str());
	}else if(aiMode){
		message->copy_label("AI mode running...");
	}else{
		message->copy_label("Move with WASD");
	}
}

void GameWindow::showSummary(){
	Player& player = game.getPlayer();
	string result = game.hasWon() ? "YOU WIN" : "YOU LOSE";
	string mode = aiMode ? "AI" : "Human";
	string text = result + "\n\n"
			+ "Mode: " + mode + "\n\n"
			+ "Score: " + to_string(player.getScore()) + "\n"
			+ "Treasure collected: " + to_string(player.getTreasuresCollected()) + "/5\n"
			+ "Lives remaining " + to_string(player.getLives()) + "\n"
			+ "Turns: " + to_string(game.getTurns());

	if(game.hasWon()){
		summary->labelcolor(fl_rgb_color(0, 255, 150));
	}else{
		summary->labelcolor(fl_rgb_color(255, 0, 100));
	}

	summary->copy_label(text.c_str());
	summary->show();

	ofstream file("last_run.txt");
	if(file){
		game.writeSummary(file, "Human");
	}
}

int GameWindow::handle(int event){
	if(!aiMode && event == FL_KEYDOWN){
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

