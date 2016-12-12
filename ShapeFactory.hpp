#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include "Shape.hpp"

class ShapeFactory {
	public:
	static void getShipShape(Shape *ship);
	static void getAsteroidShape(Shape *asteroid);
};

#endif
