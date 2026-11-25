// name: Maze.cpp
#include "Maze.h"

void Maze::load(const string& filename){
	ifstream file(filename);
	if(!file){
		throw string("Something is wrong with the file!");
	}

	int row=0;
	string line;
	while(getline(file, line)){
		if(row==SIZE){
			throw string("The maze has way too many rows!");
		}
		int length = line.size();
		if(length>0 && line[length-1] == '\r'){
			length = length-1;
		}
		if(length!=SIZE){
			throw string("A row of this maze is not large enough!");
		}
		for (int col=0; col<SIZE; col++){
			grid[row][col] = line[col];
		}
		row++;
	}
	if(row!=SIZE){
		throw string ("The maze does not have enough rows!");
	}
	validate();
	grid[playerStart.row][playerStart.col] = '.';
	for(int i=0; i<NUM_ENEMIES; i++){
		grid[enemyStarts[i].row][enemyStarts[i].col] = '.';
	}
}

void Maze::validate(){
	int players=0;
	int treasures=0;
	int enemies =0;
	int exits =0;

	for(int r=0; r<SIZE; r++){
		for(int c=0; c<SIZE; c++){
			char symbol = grid[r][c];
			if(symbol == 'P'){
				players++;
				playerStart.row = r;
				playerStart.col = c;
			}else if(symbol == 'T'){
				treasures++;
			}else if(symbol == 'E'){
				if(enemies < NUM_ENEMIES){
					enemyStarts[enemies].row = r;
					enemyStarts[enemies].col = c;
				}
				enemies++;
			}else if(symbol == 'X'){
				exits++;
			}else if(symbol !=  '#' && symbol != '.' && symbol != ' '){
				throw string("There is an unknown symbol in the maze!");
			}
		}
	}
	if(players != 1 || treasures != 5 || enemies != 3 || exits != 1){
		throw string("The maze must contain exactly 1 player, 5 treasures, 3 enemies and 1 exit");
	}
}

int Maze::getDistance(Position a, Position b){
	return abs(a.row - b.row) + abs(a.col - b.col);
}

vector<Position> Maze::collectReachableCells(Position start){
	vector<Position> reachable;
	bool visited[SIZE][SIZE] = {false};
	queue<Position> q;

	visited[start.row][start.col] = true;
	q.push(start);

	int dRow[4] = {-1, 1, 0, 0};
	int dCol[4] = {0, 0, -1, 1};

	while(!q.empty()){
		Position current = q.front();
		q.pop();
		reachable.push_back(current);

		for(int i=0; i<4; i++){
			int nRow = current.row + dRow[i];
			int nCol = current.col + dCol[i];

			if(nRow > 0 && nRow < SIZE - 1 && nCol > 0 && nCol < SIZE - 1 && !visited[nRow][nCol] && grid[nRow][nCol] == '.'){
				visited[nRow][nCol] = true;
				q.push({nRow, nCol});
			}
		}
	}

	for(int r=1; r<SIZE - 1; r++){
		for(int c=1; c<SIZE - 1; c++){
			if(grid[r][c] == '.' && !visited[r][c]){
				grid[r][c] = '#';
			}
		}
	}

	return reachable;
}

void Maze::generate(){
	vector<Position> emptyCells;
	int dRow[4] = {-1, 1, 0, 0};
	int dCol[4] = {0, 0, -1, 1};

	do{
		for(int r=0; r<SIZE; r++){
			for(int c=0; c<SIZE; c++){
				if(r == 0 || r == SIZE - 1 || c == 0 || c == SIZE - 1){
					grid[r][c] = '#';
				}else{
					grid[r][c] = '.';
				}
			}
		}

		for(int r=1; r<SIZE - 1; r++){
			for(int c=1; c<SIZE - 1; c++){
				if(rand() % 100 < 15){
					grid[r][c] = '#';
					if(rand() % 100 < 50){
						int dir = rand() % 4;
						int nRow = r + dRow[dir];
						int nCol = c + dCol[dir];
						if(nRow > 0 && nRow < SIZE - 1 && nCol > 0 && nCol < SIZE - 1){
							grid[nRow][nCol] = '#';
						}
					}
				}
			}
		}

		grid[1][1] = '.';
		emptyCells = collectReachableCells({1, 1});

	}while(emptyCells.size() < 100);

	int n = emptyCells.size();
	for(int i = n - 1; i>0; --i){
		int j = rand() % (i + 1);
		Position temp = emptyCells[i];
		emptyCells[i] = emptyCells[j];
		emptyCells[j] = temp;
	}

	vector<bool> used(n, false);

	playerStart = emptyCells[0];
	used[0] = true;

	int exitIdx = -1;
	int maxDist = -1;
	for(int i=0; i<n; i++){
		if(used[i]) continue;
		int d = getDistance(emptyCells[i], playerStart);
		if(d >= 12){
			exitIdx = i;
			break;
		}
		if(d > maxDist){
			maxDist = d;
			exitIdx = i;
		}
	}
	used[exitIdx] = true;
	grid[emptyCells[exitIdx].row][emptyCells[exitIdx].col] = 'X';

	vector<Position> placedTreasures;
	for(int t=0; t < NUM_TREASURES; t++){
		int pickIdx = -1;
		for(int i=0; i<n; i++){
			if(used[i]) continue;
			bool wellSpaced = true;
			for(const Position& other : placedTreasures){
				if(getDistance(emptyCells[i], other) < 4){
					wellSpaced = false;
					break;
				}
			}
			if(wellSpaced){
				pickIdx = i;
				break;
			}
		}
		if(pickIdx == -1){
			for(int i=0; i<n; i++){
				if(!used[i]) {pickIdx = i; break;}
			}
		}
		used[pickIdx] = true;
		placedTreasures.push_back(emptyCells[pickIdx]);
		grid[emptyCells[pickIdx].row][emptyCells[pickIdx].col] = 'T';
	}

	for(int e=0; e<NUM_ENEMIES; e++){
		int pickIdx = -1;
		for(int i=0; i<n; i++){
			if(!used[i] && getDistance(emptyCells[i], playerStart) >= 5){
				pickIdx = i;
				break;
			}
		}
		if(pickIdx == -1){
			for(int i=0; i<n; i++){
				if(!used[i]) {pickIdx = i; break;}
			}
		}
		used[pickIdx] = true;
		enemyStarts[e] = emptyCells[pickIdx];
	}
}

Maze::Maze(){
	playerStart.row = 0;
	playerStart.col = 0;
}

Position Maze::getPlayerStart() const{
	return playerStart;
}

Position Maze::getEnemyStart(int index) {
    return enemyStarts[index];
}

char Maze::getSymbol(int row, int col) const{
	return grid[row][col];
}

bool Maze::isInside(Position position){
	return position.row >= 0 && position.row < SIZE && position.col >= 0 && position.col < SIZE;
}

bool Maze::isWall(Position position){
	return grid[position.row][position.col] == '#';
}

bool Maze::isTreasure(Position position){
	return grid[position.row][position.col] == 'T';
}

void Maze::removeTreasure(Position position){
	grid[position.row][position.col] = '.';
}

bool Maze::isExit(Position position){
	return grid[position.row][position.col] == 'X';
}

int Maze::countTreasures(){
	int count = 0;
	for(int r=0; r<SIZE; r++){
		for(int c=0; c<SIZE; c++){
			if(grid[r][c] == 'T'){
				count++;
			}
		}
	}
	return count;
}
