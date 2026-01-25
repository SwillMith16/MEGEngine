#include "entity.h"
#include "transform.h"
#include "mesh_renderer.h"
#include "utils/log.h"

namespace MEGEngine {
	Entity::Entity() : _transform(std::make_unique<Transform>()){}

	Transform& Entity::transform() {
		return *_transform;
	}

	MeshRenderer *Entity::meshRenderer() {
		return _meshRenderer.get();
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

	void Entity::draw(Camera &camera) {
		if (_meshRenderer) {
			_meshRenderer->draw(camera, *_transform);
		}
		else {
			Log(LogLevel::WRN, "Cannot draw entity that has no mesh renderer");
		}

		for (Entity* child : _children) {
			child->draw(camera);
		}
	}
}
