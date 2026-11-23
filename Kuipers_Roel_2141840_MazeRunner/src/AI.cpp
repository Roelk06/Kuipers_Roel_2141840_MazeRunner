// name: AI.cpp
#include "AI.h"

struct Node{
	Position pos;
	int g;
	int f;

	bool operator>(const Node& other) const{
		return f > other.f;
	}
};

int AI::getDistance(Position a, Position b){
	return abs(a.row - b.row) + abs(a.col - b.col);
}

bool AI::isDangerCell(Game& game, Position pos, bool avoidAdjacent){
	if(game.isEnemyAt(pos)){
		return true;
	}
	if(avoidAdjacent){
		int dRow[4] = {-1, 1, 0, 0};
		int dCol[4] = {0, 0, -1, 1};
		for(int i=0; i<4; i++){
			Position adj = {pos.row + dRow[i], pos.col + dCol[i]};
			if(adj.row >= 0 && adj.row < SIZE && adj.col >= 0 && adj.col < SIZE){
				if(game.isEnemyAt(adj)){
					return true;
				}
			}
		}
	}
	return false;
}

Position AI::chooseTarget(Game& game, Position start){
	char goalSymbol = (game.getTreasuresLeft() > 0) ? 'T' : 'X';
	Position bestTarget = start;
	int minDist = 9999;

	for(int r=0; r<SIZE; r++){
		for(int c=0; c<SIZE; c++){
			if(game.getMazeSymbol(r, c) == goalSymbol){
				Position candidate = {r, c};
				int dist = getDistance(start, candidate);
				if(dist < minDist){
					minDist = dist;
					bestTarget = candidate;
				}
			}
		}
	}
	return bestTarget;
}

char AI::posToDirection(Position from, Position to){
	if(to.row < from.row) return 'w';
	if(to.row > from.row) return 's';
	if(to.col < from.col) return 'a';
	if(to.col > from.col) return 'd';
	return '\0';
}

char AI::findNextStepAStar(Game& game, Position start, Position target, bool avoidAdjacent){
	if(start.row == target.row && start.col == target.col) return '\0';

	priority_queue<Node, vector<Node>, greater<Node>> openSet;
	int gScore[SIZE][SIZE];
	Position cameFrom[SIZE][SIZE];
	bool closed[SIZE][SIZE];

	for(int r=0; r<SIZE; r++){
		for(int c=0; c<SIZE; c++){
			gScore[r][c] = 9999;
			cameFrom[r][c] = {-1, -1};
			closed[r][c] = false;
		}
	}

	gScore[start.row][start.col] = 0;
	openSet.push({start, 0, getDistance(start, target)});

	int dRow[4] = {-1, 1, 0, 0};
	int dCol[4] = {0, 0, -1, 1};
	bool found = false;

	while(!openSet.empty()){
		Node current = openSet.top();
		openSet.pop();

		int r = current.pos.row;
		int c = current.pos.col;

		if(closed[r][c]) continue;
		closed[r][c] = true;

		if(r == target.row && c == target.col){
			found = true;
			break;
		}

		for(int i=0; i<4; i++){
			Position next = {r + dRow[i], c + dCol[i]};

			if(next.row < 0 || next.row >= SIZE || next.col < 0 || next.col >= SIZE) continue;
			if(closed[next.row][next.col]) continue;
			if(game.getSymbol(next.row, next.col) == '#') continue;
			if(game.isEnemyAt(next)) continue;

			int stepCost = 1;
			if(avoidAdjacent && isDangerCell(game, next, true)){
				stepCost = 15;
			}

			int tentativeG = gScore[r][c] + stepCost;
			if(tentativeG < gScore[next.row][next.col]){
				gScore[next.row][next.col] = tentativeG;
				cameFrom[next.row][next.col] = current.pos;
				int f = tentativeG + getDistance(next, target);
				openSet.push({next, tentativeG, f});
			}
		}
	}

	if(!found) return '\0';

	Position step = target;
	while(!(cameFrom[step.row][step.col].row == start.row && cameFrom[step.row][step.col].col == start.col)){
		step = cameFrom[step.row][step.col];
	}

	return posToDirection(start, step);
}

char AI::getNextMove(Game& game){
	Position start = game.getPlayer().getPosition();
	Position target = chooseTarget(game, start);

	char move = findNextStepAStar(game, start, target, true);
	if(move != '\0'){
		return move;
	}

	move = findNextStepAStar(game, start, target, false);
	if(move != '\0'){
		return move;
	}

	int dRow[4] = {-1, 1, 0, 0};
	int dCol[4] = {0, 0, -1, 1};
	char dirs[4] = {'w', 's', 'a', 'd'};

	char bestDir = 'w';
	int maxSafetyDist = -1;

	for (int i = 0; i < 4; i++) {
		Position next = {start.row + dRow[i], start.col + dCol[i]};
		if (next.row >= 0 && next.row < SIZE && next.col >= 0 && next.col < SIZE){
			if (game.getSymbol(next.row, next.col) != '#' && !game.isEnemyAt(next)){
				int closestEnemy = 9999;
	            for(int r=0; r<SIZE; r++){
	            	for(int c=0; c<SIZE; c++){
	            		if(game.isEnemyAt({r, c})){
	            			int d = getDistance(next, {r, c});
	                        if (d < closestEnemy) closestEnemy = d;
	            		}
	            	}
	            }
	            if(closestEnemy > maxSafetyDist){
	            	maxSafetyDist = closestEnemy;
	            	bestDir = dirs[i];
	            }
			}
		}
	}
	return bestDir;
}


