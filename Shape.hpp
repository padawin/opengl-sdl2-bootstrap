#ifndef __SHAPE__
#define __SHAPE__

#include <GL/glew.h>

class Shape {
	protected:
	GLfloat *m_fVertices;
	GLuint *m_iElements;
	unsigned long m_iNbVertices;
	unsigned long m_iNbElements;
	GLuint vertexArray,
		vertexBuffer,
		elementsBuffer;

	public:
	void setVertices(GLfloat *vertices, unsigned long nbVertices);
	void setElements(GLuint *elements, unsigned long nbElements);
	~Shape();
	GLfloat *getVertices();
	GLuint *getElements();
	unsigned long getNbVertices();
	unsigned long getNbElements();
};

#endif
