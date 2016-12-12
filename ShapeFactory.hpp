#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include "Shape.hpp"

enum ShapeType {SHIP, ASTEROID};

class ShapeFactory {
	private:
	static void _getShipShape(Shape *ship);
	static void _getAsteroidShape(Shape *asteroid);

	public:
	static void getShape(ShapeType type, Shape *shape);
};

#endif
