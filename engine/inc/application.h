#ifndef MEGENGINE_APPLICATION_H
#define MEGENGINE_APPLICATION_H

#include <memory>
#include <string>

#include "common.h"

namespace MEGEngine {
	class Window;
	class Scene;
	class Renderer;

	struct ENGINE_API ApplicationConfig {
		std::string windowTitle = "MEGEngine Game";
		int width = 1280;
		int height = 720;
		bool fullscreen = false;
		bool vsync = true;
	};

	class ENGINE_API Application {
	public:
		ApplicationConfig config;

		// Create instance using ApplicationConfig structure
		explicit Application(const ApplicationConfig& config);
		// Create instance using default configuration
		Application() = default;
		// Overwritable destructor so instance can handle its own clean-up
		virtual ~Application();

		// Prevents copying of the instance
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		// Prevents moving the instance
		Application(Application&&) noexcept;
		Application& operator=(Application&&) noexcept;

		// Handles the main loop
		void run();
		// Handles application exit
		void requestQuit();

		// Return window object owned by the application
		Window& window();

		// Return scene object owned by the application
		Scene& scene();

		// Return renderer object owned by the application
		// Renderer& renderer();

		// getter for delta time to allow for synchronised time across the application
		float deltaTime() const;

	protected:
		// Virtual function, overwritten by objects of this class. Called on application startup
		virtual void onInit() {}
		// Virtual function, overwritten by objects of this class. Called on each frame
		virtual void onUpdate(float dt) {};
		// Virtual function, overwritten by objects of this class. Called on application exit
		virtual void onShutdown() {};

	private:
		// Internal function to create necessary objects
		void init();
		// Internal function to handle application exit
		void shutdown();
		// Internal function to encapsulate deltaTime calculation
		void setDeltaTime(auto& _lastTime);

		bool running = false;
		float _deltaTime = 0.0f;

		std::unique_ptr<Window> _window;
		// std::unique_ptr<Renderer> _renderer;
		std::unique_ptr<Scene> _scene;
	};
} // MEGEngine

#endif //MEGENGINE_APPLICATION_H