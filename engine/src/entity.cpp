#include "MEGEngine/entity.h"
#include "MEGEngine/transform.h"
#include "MEGEngine/mesh_renderer.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
	Transform& Entity::transform() {
		return *_transform;
	}

	std::shared_ptr<MeshRenderer> Entity::meshRenderer() {
		return _meshRenderer;
	}
	void Entity::setMeshRenderer(std::shared_ptr<MeshRenderer> renderer) {
		_meshRenderer = std::move(renderer);
	}

	void Entity::addChild(Entity& child) {
		if (child._parent) {
			auto& siblings = child._parent->_children;
			for (unsigned i = 0; i < siblings.size(); i++) {
				if (siblings[i] == &child) {
					siblings.erase(siblings.begin() + i);
				}
			}
		}

		child._parent = this;
		_children.push_back(&child);
	}

	const std::vector<Entity*>& Entity::children() const { return _children; }

	Entity *Entity::parent() const { return _parent; }
}
