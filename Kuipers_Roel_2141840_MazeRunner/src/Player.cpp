// name: Player.cpp
#include "Player.h"

Player::Player(): Character(){
	lives = START_LIVES;
	score = 0;
	treasure_collected = 0;
}

int Player::getLives() const{
	return lives;
}

int Player::getScore() const{
	return score;
}

int Player::getTreasuresCollected() const{
	return treasure_collected;
}

void Player::loseLife(){
	lives--;
}

void Player::collectTreasure(){
	treasure_collected++;
	score += TREASURE_POINTS;
}
