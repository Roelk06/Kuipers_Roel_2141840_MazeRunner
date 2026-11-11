#ifndef GAME_H_
#define GAME_H_

#include "Maze.h"
#include "Player.h"
#include "Enemy.h"

class Game{
	private:
		Maze maze;
		Player player;
		Enemy enemies[NUM_ENEMIES];
		string message;
		int turns;
		bool won;
		Position nextPosition(char direction);
		bool movePlayer(char direction);
		void collectTreasure();
		bool isEnemyAt(Position position) const;
		bool canEnemyMoveTo(Position position);
		void moveEnemy(Enemy& enemy);
		void checkCollision();
		void checkExit();
	public:
		Game();
		void load(const string& filename);
		bool playTurn(char direction);
		char getSymbol(int row, int col) const;
		Player& getPlayer();
		string getMessage();
		int getTurns();
		int getTreasuresLeft();
		bool hasWon();
		bool isOver();
		void writeSummary(ostream& out, string mode);
};

#endif // GAME_H_
