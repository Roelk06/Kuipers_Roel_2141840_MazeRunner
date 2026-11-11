#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Position.h"

class Character{
	private:
		Position position;
	public:
		Character();
		Position getPosition() const;
		void setPosition(Position newposition);
		bool isAt(Position cell);
};

#endif // CHARACTER_H_
