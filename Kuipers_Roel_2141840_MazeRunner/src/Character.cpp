// name: Character.cpp
#include "Character.h"

Character::Character(){
	position.row = 0;
	position.col = 0;
}

Position Character::getPosition() const{
	return position;
}

void Character::setPosition(Position newposition){
	position = newposition;
}

bool Character::isAt(Position cell){
	return position.row == cell.row && position.col == cell.col;
}
