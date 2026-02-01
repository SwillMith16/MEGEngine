#include <chrono>
#include <thread>

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "MEGEngine/application.h"
#include "MEGEngine/window.h"
#include "MEGEngine/scene.h"
#include "MEGEngine/renderer.h"
#include "MEGEngine/camera.h"
#include "MEGEngine/settings.h"
#include "MEGEngine/input.h"

#include "MEGEngine/utils/log.h"

namespace MEGEngine {
	using clock = std::chrono::high_resolution_clock;

	Application::Application(const ApplicationConfig& appConfig) {
		this->config = appConfig;
		// TODO: store app config values in settings for global use throughout application
	}

	Application::~Application() {
		if (running) shutdown();
	}

	Application::Application(Application &&) noexcept = default;
	Application& Application::operator=(Application &&) noexcept = default;

	void Application::run() {
		init();
		running = true;

		auto lastTime = clock::now();

		while (running) {
			_scene->update(_deltaTime);
			// _scene->camera().processInputs(window(), deltaTime()); // TODO: until input manager is added
			InputManager::processInputs();

	    	_renderer->render(*_scene);

	    	_window->display();
	    	_window->pollEvents();

	    	if (_window->shouldClose())
	    		requestQuit();

	        // Limit FPS and set deltaTime
	    	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	    	setDeltaTime(lastTime);
			onUpdate(_deltaTime);
	    }

	    // close
	    shutdown();

	}

	void Application::requestQuit() {
		running = false;
	}

	float Application::deltaTime() const {
		return _deltaTime;
	}

	Window& Application::window() {
		return *_window;
	}

	Scene& Application::scene() {
		return *_scene;
	}

	Renderer& Application::renderer() {
		return *_renderer;
	}

	void Application::init() {
		settings.init();

		_window = std::make_unique<Window>();
		_window->create(config.windowTitle, config.width, config.height);

		InputManager::init(_window.get());

		// load glad for access to GL functions
		int status = gladLoadGL();
		if (!status) {
			glfwTerminate();
			throw std::runtime_error("Failed to initialize GLAD");
		}

		// set the viewport
		glViewport(0, 0, config.width, config.height);

		// enables depth perception - prevents incorrect overlapping triangles
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		_renderer = std::make_unique<Renderer>();
		_renderer->init();

		_scene = std::make_unique<Scene>(config.width, config.height);

		onInit();
	}

	void Application::shutdown() {
		onShutdown();

		_scene.reset();
		_renderer.reset();
		_window.reset();
	}

	void Application::setDeltaTime(auto& lastTime) {
		auto now = clock::now();
		std::chrono::duration<float> delta = now - lastTime;
		lastTime = now;
		_deltaTime = delta.count();
	}
} // MEGEngine