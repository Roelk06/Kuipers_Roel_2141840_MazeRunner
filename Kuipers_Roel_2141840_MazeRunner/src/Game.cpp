// name: Game.
#include "Game.h"

Game::Game(){
	message = "";
	turns = 0;
	won = false;
}

void Game::load(const string& filename){
	maze.load(filename);
	player.setPosition(maze.getPlayerStart());
	for(int i=0; i<NUM_ENEMIES; i++){
		enemies[i].setPosition(maze.getEnemyStart(i));
	}
	message = "";
}

bool Game::playTurn(char direction){
	message = "";
	if(!movePlayer(direction)){
		message = "Invalid move, you stay where you are!";
		return false;
	}
	collectTreasure();
	checkCollision();
	checkExit();

	if(!won){
		for(int i=0; i<NUM_ENEMIES; i++){
			bool isSmart = (i==0);
			moveEnemy(enemies[i], isSmart);
			checkCollision();
		}
	}


	turns++;
	return true;
}

Position Game::nextPosition(char direction){
	Position next = player.getPosition();
	if(direction == 'w' || direction == 'W'){
		next.row--;
	}else if(direction == 'a' || direction == 'A'){
		next.col--;
	}else if(direction == 'd' || direction == 'D'){
		next.col++;
	}else if(direction == 's' || direction == 'S'){
		next.row++;
	}
	return next;
}

bool Game::movePlayer(char direction){
	Position current = player.getPosition();
	Position next = nextPosition(direction);

	if(next.row == current.row && next.col == current.col){
		return false;
	}
	if(!maze.isInside(next) || maze.isWall(next)){
		return false;
	}
	player.setPosition(next);
	return true;
}

char Game::getSymbol(int row, int col) const{
	Position here;
	here.row = row;
	here.col = col;
	Position position = player.getPosition();
	if(row == position.row && col == position.col){
		return 'P';
	}
	if(isEnemyAt(here)){
		return 'E';
	}
	return maze.getSymbol(row, col);
}

void Game::collectTreasure(){
	Position position = player.getPosition();
	if(maze.isTreasure(position)){
		maze.removeTreasure(position);
		player.collectTreasure();
		message = "Treasure collected, 10 points for you!";
	}
}

void Game::checkCollision(){
	if(isEnemyAt(player.getPosition())){
		player.loseLife();
		player.setPosition(maze.getPlayerStart());
		message = "You're hit, get back to start!";
	}
}

void Game::checkExit(){
	if(!maze.isExit(player.getPosition())){
		return;
	}
	if(maze.countTreasures() == 0){
		won = true;
		message = "You did it!";
	}else{
		message = "Please collect all the treasure!";
	}
}

bool Game::isEnemyAt(Position position) const{
	for(int i=0; i<NUM_ENEMIES; i++){
		Position enemy = enemies[i].getPosition();
		if(enemy.row == position.row && enemy.col == position.col){
			return true;
		}
	}
	return false;
}

bool Game::canEnemyMoveTo(Position position){
	if(!maze.isInside(position) || maze.isWall(position)){
		return false;
	}
	Position start = maze.getPlayerStart();
	if(position.row == start.row && position.col == start.col){
		return false;
	}
	return !isEnemyAt(position);

}

int getDistance(Position a, Position b){
	return abs(a.row - b.row) + abs(a.col - b.col);
}

void Game::moveEnemy(Enemy& enemy, bool isSmart){
	int rowSteps[4] = {-1, 1, 0, 0};
	int colSteps[4] = {0, 0, -1, 1};
	Position options[4];
	int count = 0;

	for(int i=0; i<4; i++){
		Position next = enemy.getPosition();
		next.row += rowSteps[i];
		next.col += colSteps[i];
		if(canEnemyMoveTo(next)){
			options[count] = next;
			count++;
		}
	}
	if(count>0){
		if(isSmart && (rand() % 100 < 75)){
			Position playerPos = player.getPosition();
			int bestIndex = 0;
			int minDistance = 999;

			for(int i=0; i<count; i++){
				int dist = getDistance(options[i], playerPos);
				if(dist < minDistance){
					minDistance = dist;
					bestIndex = i;
				}
			}
			enemy.setPosition(options[bestIndex]);
		}else{
			enemy.setPosition(options[rand() % count]);
		}
	}
}

Player& Game::getPlayer() {
    return player;
}

string Game::getMessage() {
    return message;
}

int Game::getTurns(){
	return turns;
}
int Game::getTreasuresLeft(){
	return maze.countTreasures();
}

bool Game::isOver() {
    return won || player.getLives() <= 0;
}

bool Game::hasWon(){
	return won;
}

void Game::writeSummary(ostream& out, string mode){
	string result = "STOPPED";
	if(won){
		result = "YOU WIN";
	}else if(player.getLives() <= 0){
		result = "YOU LOSE";
	}
	out << "        GAME OVER" << endl;
	out << endl;
	out << "Mode: " << mode << endl;
	out << "Result: " << result << endl;
	out << endl;
	out << "Score: " << player.getScore() << endl;
	out << "Treasure collected: " << player.getTreasuresCollected() << "/" << NUM_TREASURES << endl;
	out << "Lives remaining: " << player.getLives() << endl;
	out << "Turns: " << turns << endl;
}

