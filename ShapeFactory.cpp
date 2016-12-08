#include "ShapeFactory.hpp"
#include <stdio.h>

Shape ShapeFactory::getShipShape() {
	GLfloat vertices[] = {
		// Position    Color             Texcoords
		// roof
		0.0f,   0.3f, -0.75f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.75f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.75f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		// walls
		0.5f,   0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		-0.5f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		0.5f,  -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	};
	GLuint elements[] = {
		0, 2, 1,
		3, 4, 5,
		4, 3, 6
	};

	Shape ship;
	ship.setVertices(vertices, sizeof(vertices));
	ship.setElements(elements, sizeof(elements));
	return ship;
}

Shape ShapeFactory::getAsteroidShape() {
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};
	GLuint elements[] = {
		// back
		0, 2, 1,
		0, 3, 2,
		// front
		4, 5, 6,
		4, 6, 7,
		// top
		7, 6, 2,
		7, 2, 3,
		// bottom
		4, 1, 5,
		4, 0, 1,
		// left
		4, 3, 0,
		4, 7, 3,
		// right
		5, 1, 2,
		5, 2, 6
	};

	Shape asteroid;
	asteroid.setVertices(vertices, sizeof(vertices));
	asteroid.setElements(elements, sizeof(elements));
	return asteroid;
}
