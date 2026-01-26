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
#include "shader_priv.h"
#include "shader_manager.h"
#include "texture.h"
#include "camera.h"
#include "material.h"
#include "primitive_shapes.h"

#include "math/quat.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/vec2.h"

#include "math/glm_conversions.h"
#include "utils/log.h"

const GLint g_windowWidth = 800, g_windowHeight = 800;

namespace MEGEngine {
	using clock = std::chrono::high_resolution_clock;

	Application::Application(const ApplicationConfig& appConfig) {
		this->config = appConfig;
	}

	Application::~Application() {
		if (running) shutdown();
	}

	Application::Application(Application &&) noexcept = default;
	Application& Application::operator=(Application &&) noexcept = default;

	void Application::run() {
		init();

		// initialise GLFW and set some data for the window
	    glfwInit();
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	    // create window object
	    GLFWwindow* window = glfwCreateWindow(g_windowWidth, g_windowHeight, "MEGEngine", nullptr, nullptr);
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
	    glViewport(0, 0, g_windowWidth, g_windowHeight);

		// enables depth perception - prevents incorrect overlapping triangles
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		Vec4 lightColour = Vec4(1.0f, 1.0f, 1.0f, 1.0f);


		Entity light = Entity();
		modelLoader.loadModelFromData(light, Cube::vertices(), Cube::indices());
		std::vector<Texture> tex {Texture("", "diffuse", 0)};
		light.meshRenderer()->setMaterial(std::make_shared<Material>(ShaderManager::getShader("light")));
		light.meshRenderer()->material()->setTextureList(tex);
		if (light.meshRenderer()->material()->shader()) {
			light.meshRenderer()->material()->shader()->activate();
			light.meshRenderer()->material()->shader()->setUniform("lightColour", lightColour);
			light.meshRenderer()->material()->shader()->setUniform("translation", light.transform().position());
		}


		Entity sword = Entity();
		modelLoader.loadModelFromFile(sword, (settings.general().modelDirectory + "/sword/sword.gltf").c_str());
		sword.transform().setPosition(Vec3(-5, -5, 0));
		sword.transform().setRotation(Quat(0, 0, 0.707, 0.707));
		sword.transform().setScale(0.5);
		sword.meshRenderer()->material()->shader()->activate();
		sword.meshRenderer()->material()->shader()->setUniform("lightColour", lightColour);
		sword.meshRenderer()->material()->shader()->setUniform("lightPos", light.transform().position());


		Vec3 cameraPos = Vec3(0.0f, 0.0f, -10.0f);
		Camera camera(g_windowWidth, g_windowHeight, cameraPos);
		// camera.orientation = glm::rotate(camera.orientation, glm::radians(-45.0f), camera.up); // left-right rotation
		camera.orientation = Private::fromGlmVec3(glm::rotate(Private::toGlmVec3(camera.orientation), glm::radians(-20.0f), glm::normalize(glm::cross(Private::toGlmVec3(camera.orientation), Private::toGlmVec3(camera.up))))); // up-down rotation


		auto lastTime = clock::now();

	    while (!glfwWindowShouldClose(window)) {

	        // set background colour
	        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	        // clean back buffer and depth buffer
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    	sword.transform().setPosition(sword.transform().position() + (Vec3(1, 0, 0) * deltaTime()));

	        camera.processInputs(window, deltaTime());
    		camera.updateMatrix(70.0f, 0.1f, 1000.0f);

	    	sword.draw(camera);
	    	light.draw(camera);

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

	// Scene& Application::scene() {
	// 	return *_scene;
	// }

	// Renderer& Application::renderer() {
	// 	return *_renderer;
	// }

	void Application::init() {
		settings.init();
		// gladLoadGL();
		// glViewport(0, 0, config.width, config.height);

		// setup window, renderer, and scene


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