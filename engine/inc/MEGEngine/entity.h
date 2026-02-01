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

		// Template allows for sub-types of EventListener to be attached to an entity
		template<typename ListenerType, typename EventType>
		void createEventListener()
		{
			static_assert(std::is_base_of_v<EventListener, ListenerType>);
			static_assert(std::is_base_of_v<Event, EventType>);

			auto listener = std::make_unique<ListenerType>(*this);
			ListenerType& ref = *listener;
			_listeners.push_back(std::move(listener));
			EventManager::addListener<EventType>(ref);
		}

	protected:
		Entity* _parent = nullptr;
		std::vector<Entity*> _children;
		std::unique_ptr<Transform> _transform = std::make_unique<Transform>();
		std::shared_ptr<MeshRenderer> _meshRenderer;
		std::vector<std::unique_ptr<EventListener>> _listeners;
	};
}


#endif //MODEL_H