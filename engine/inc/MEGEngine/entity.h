#ifndef MODEL_H
#define MODEL_H

#include <vector>

#include "MEGEngine/common.h"
#include "MEGEngine/transform.h"
#include "MEGEngine/mesh_renderer.h"
#include "MEGEngine/events.h"

namespace MEGEngine {
	class ENGINE_API Entity {
	public:
		Entity() = default;
		virtual ~Entity() = default;

		virtual void onUpdate() {} // TODO: update will be moved to script component when script feature is added

		Transform& transform() const;
		std::shared_ptr<MeshRenderer> meshRenderer();

		void setMeshRenderer(std::shared_ptr<MeshRenderer> renderer);

		void addChild(Entity& child);
		[[nodiscard]] const std::vector<Entity*>& children() const;
		[[nodiscard]] Entity* parent() const;

	protected:
		Entity* _parent = nullptr;
		std::vector<Entity*> _children;
		std::unique_ptr<Transform> _transform = std::make_unique<Transform>();
		std::shared_ptr<MeshRenderer> _meshRenderer;
	};
}


#endif //MODEL_H