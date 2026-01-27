#include "application.h"

#include <chrono>
#include <thread>

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"
#include "GLM/gtx/rotate_vector.hpp"

// #include "window.h"
// #include "scene.h"
// #include "renderer.h"

#include "mesh.h"
#include "settings.h"
#include "entity.h"
#include "model_loader.h"
#include "shader.h"
#include "shader_manager.h"
#include "texture.h"
#include "camera.h"
#include "material.h"
#include "primitive_shapes.h"
#include "scene.h"

#include "math/quat.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/vec2.h"

#include "math/glm_conversions.h"
#include "utils/log.h"

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

		// initialise GLFW and set some data for the window
	    glfwInit();
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	    // create window object
	    GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.windowTitle.c_str(), nullptr, nullptr);
	    if (!window) {
	        glfwTerminate();
	        throw std::runtime_error("Failed to create GLFW window");
	    }

	    // apply actions to this window (make it the current context)
	    glfwMakeContextCurrent(window);

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


		init();

		_scene->camera().setPosition({0, 0, -10});
		_scene->camera().orientation = Private::fromGlmVec3(glm::rotate(Private::toGlmVec3(_scene->camera().orientation), glm::radians(-20.0f), glm::normalize(glm::cross(Private::toGlmVec3(_scene->camera().orientation), Private::toGlmVec3(_scene->camera().up))))); // up-down rotation

		auto lastTime = clock::now();

	    while (!glfwWindowShouldClose(window)) {

	        // set background colour
	        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	        // clean back buffer and depth buffer
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    	_scene->update(_deltaTime);


	        _scene->camera().processInputs(window, deltaTime());
    		_scene->camera().updateMatrix(70.0f, 0.1f, 1000.0f);

	    	for (auto& entity: _scene->entities()) {
	    		entity->draw(_scene->camera());
	    	}

	        // bring buffer to the front
	        glfwSwapBuffers(window);

	        // poll for events, otherwise program doesn't respond
	        glfwPollEvents();

	        // Limit FPS and set deltaTime
	    	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	    	setDeltaTime(lastTime);
	    }

	    // close
	    glfwDestroyWindow(window);
	    glfwTerminate();

	}

	void Application::requestQuit() {
		running = false;
	}

	float Application::deltaTime() const {
		return _deltaTime;
	}

	// Window& Application::window() {
	// 	return *_window;
	// }

	Scene& Application::scene() {
		return *_scene;
	}

	// Renderer& Application::renderer() {
	// 	return *_renderer;
	// }

	void Application::init() {
		settings.init();

		// setup window, renderer, and scene
		_scene = std::make_unique<Scene>(config.width, config.height);


		onInit();
	}

	void Application::shutdown() {
		onShutdown();

		// _scene.reset();
		// _renderer.reset();
		// _window.reset();
	}

	void Application::setDeltaTime(auto& lastTime) {
		auto now = clock::now();
		std::chrono::duration<float> delta = now - lastTime;
		lastTime = now;
		_deltaTime = delta.count();
	}
} // MEGEngine