#include "RenderableCollection.hpp"
#include <stdlib.h>

void RenderableCollection::addShape(ShapeType shapeType) {
	if (m_mShapes.find(shapeType) != m_mShapes.end()) {
		return;
	}

	m_mShapes[shapeType] = new Shape();
	ShapeFactory::getShape(shapeType, m_mShapes[shapeType]);
	m_lVerticesSize += m_mShapes[shapeType]->getNbVertices();
	m_lElementsSize += m_mShapes[shapeType]->getNbElements();
}

void RenderableCollection::generateBuffers() {
	glGenBuffers(1, &m_iVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_iVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_lVerticesSize, 0, GL_STATIC_DRAW);

	unsigned long offset = 0;
	for (auto& shape : m_mShapes) {
		glBufferSubData(
			GL_ARRAY_BUFFER,
			offset,
			shape.second->getNbVertices(),
			shape.second->getVertices()
		);
		offset += shape.second->getNbVertices();
	}

	glGenBuffers(1, &m_iElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_lElementsSize, 0, GL_STATIC_DRAW);

	offset = 0;
	for (auto& shape : m_mShapes) {
		glBufferSubData(
			GL_ELEMENT_ARRAY_BUFFER,
			offset,
			shape.second->getNbElements(),
			shape.second->getElements()
		);
		m_mShapesOffsets[shape.first] = offset;
		offset += shape.second->getNbElements();
	}
}

void RenderableCollection::generateVertexArrays(GLuint shaderProgram) {
	unsigned long sizeFloat = sizeof(GLfloat);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texture");

	unsigned long offset = 0;
	for (auto& shape : m_mShapes) {
		GLuint vertexArray = 0;
		m_mVertexArrays[shape.first] = vertexArray;
		glGenVertexArrays(1, &m_mVertexArrays[shape.first]);
		bindVertexArray(shape.first);
		glEnableVertexAttribArray(posAttrib);
		glEnableVertexAttribArray(colAttrib);
		glEnableVertexAttribArray(texAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, m_iVertexBuffer);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeFloat, (void*) offset);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeFloat, (void*)(offset + 3 * sizeFloat));
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeFloat, (void*)(offset + 6 * sizeFloat));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iElementBuffer);
		offset += shape.second->getNbVertices();
	}
}

void RenderableCollection::clean() {
	glDeleteBuffers(1, &m_iVertexBuffer);
	glDeleteBuffers(1, &m_iElementBuffer);
	for (auto vertexArray : m_mVertexArrays) {
		glDeleteVertexArrays(1, &vertexArray.second);
	}
	for (auto shape : m_mShapes) {
		free(shape.second);
	}
}

void RenderableCollection::bindVertexArray(ShapeType type) {
	glBindVertexArray(m_mVertexArrays[type]);
}

void RenderableCollection::render(ShapeType type) {
	glDrawElements(
		GL_TRIANGLES,
		m_mShapes[type]->getNbElements() / sizeof(GLuint),
		GL_UNSIGNED_INT,
		(void*) m_mShapesOffsets[type]
	);
}
