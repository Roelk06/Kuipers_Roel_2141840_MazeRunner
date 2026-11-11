// name: Maze.cpp
#include <fstream>
#include <iostream>
#include "Maze.h"
using namespace std;

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

Maze::Maze(){
	playerStart.row = 0;
	playerStart.col = 0;
}

Position Maze::getPlayerStart() const{
	return playerStart;
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

Position Maze::getEnemyStart(int index) {
    return enemyStarts[index];
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
