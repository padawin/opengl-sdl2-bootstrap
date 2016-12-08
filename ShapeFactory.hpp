#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include "Shape.hpp"

class ShapeFactory {
	public:
	static Shape getShipShape();
	static Shape getAsteroidShape();
};

#endif
