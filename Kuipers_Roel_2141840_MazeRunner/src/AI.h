#ifndef AI_H_
#define AI_H_

#include <functional>
#include "Game.h"

class AI {
	private:
		int getDistance(Position a, Position b);
		bool isDangerCell(Game& game, Position pos, bool avoidAdjacent);
		Position chooseTarget(Game& game, Position start);
		char findNextStepAStar(Game &game, Position start, Position target, bool avoidAdjacent);
		char posToDirection(Position from, Position to);
	public:
		char getNextMove(Game& game);
};

#endif // AI_H_
