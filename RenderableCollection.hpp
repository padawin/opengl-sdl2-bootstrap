#ifndef __RENDERABLE_COLLECTION__
#define __RENDERABLE_COLLECTION__

#include <map>
#include <vector>
#include "ShapeFactory.hpp"
#include "Shape.hpp"

class RenderableCollection {
	protected:
	unsigned long m_lVerticesSize;
	unsigned long m_lElementsSize;
	std::map<ShapeType, GLuint> m_mVertexArrays;
	std::map<ShapeType, Shape*> m_mShapes;
	std::map<ShapeType, unsigned long> m_mShapesOffsets;
	GLuint m_iVertexBuffer;
	GLuint m_iElementBuffer;

	public:
	RenderableCollection() : m_lVerticesSize(0), m_lElementsSize(0) {}
	void addShape(ShapeType shapeType);
	void generateBuffers();
	void generateVertexArrays(GLuint shaderProgram);
	void clean();
	void bindVertexArray(ShapeType type);
	void render(ShapeType type);
};

#endif
