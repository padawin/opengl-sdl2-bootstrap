#include "EntityCollection.hpp"

void EntityCollection::addEntity(Entity *entity) {
	ShapeType type = entity->getShapeType();
	if (m_mEntities.find(type) == m_mEntities.end()) {
		m_mEntities[type] = std::vector<Entity*>();
	}

	m_mEntities[type].push_back(entity);
}

void EntityCollection::flush() {
	m_mEntities.clear();
}

void EntityCollection::update() {
	for (auto& it : m_mEntities) {
		for (auto &itEntity : it.second) {
			itEntity->update();
		}
	}
}

void EntityCollection::render(GLuint shaderProgram, RenderableCollection renderables) {
	for (auto& it : m_mEntities) {
		renderables.bindVertexArray(it.first);
		for (auto &itEntity : it.second) {
			glm::mat4 trans = itEntity->getTransformationMatrix();
			GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
			renderables.render(it.first);
		}
	}
}
