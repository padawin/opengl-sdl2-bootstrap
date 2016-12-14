#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.hpp"

class Player : public Entity {
	public:
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
};

#endif
