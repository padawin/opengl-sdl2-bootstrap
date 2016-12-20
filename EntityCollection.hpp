#ifndef __ENTITY_COLLECTION__
#define __ENTITY_COLLECTION__

#include <map>
#include <vector>
#include "ShapeFactory.hpp"
#include "Entity.hpp"
#include "RenderableCollection.hpp"

class EntityCollection {
	protected:
	std::map<ShapeType, std::vector<Entity*>> m_mEntities;

	public:
	void addEntity(Entity *entity);
	void flush();
	void update();
	void render(GLuint shaderProgram, RenderableCollection renderables);
};

#endif
