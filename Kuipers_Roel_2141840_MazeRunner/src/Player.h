#ifndef PLAYER_H_
#define PLAYER_H_

#include "Character.h"

const int START_LIVES = 3;
const int TREASURE_POINTS = 10;

class Player: public Character{
	private:
		int lives;
		int score;
		int treasure_collected;
	public:
		Player();
		int getLives() const;
		int getScore() const;
		int getTreasuresCollected() const;
		void loseLife();
		void collectTreasure();
};


#endif // PLAYER_H_
