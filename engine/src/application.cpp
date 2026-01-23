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
#include "model.h"
#include "shader.h"
#include "shader_priv.h"
#include "texture.h"
#include "camera.h"

#include "math/quat.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/vec2.h"

#include "math/glm_conversions.h"

const GLint g_windowWidth = 800, g_windowHeight = 800;

//TODO: move all engine code into MEGEngine namespace

MEGEngine::Vertex lightVertices[] =
{
	//                  Position                       /                  Normal                 /                 Colours                /           Texture Coords            //
	// top
	//TODO: abstract all use of glm types into engine types
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f,  1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f,  1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},

	// front
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f, -1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f,  1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},

	// right
	MEGEngine::Vertex{MEGEngine::Vec3(01.0, -01.0,  01.0), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(01.0, -01.0, -01.0), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(01.0,  01.0, -01.0), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(01.0,  01.0,  01.0), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},

	// back
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f, -1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f,  1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},

	// left
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f,  1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},

	// bottom
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f, -1.0f, -1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3( 1.0f, -1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)},
	MEGEngine::Vertex{MEGEngine::Vec3(-1.0f, -1.0f,  1.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec3(0.0f,  0.0f,  0.0f), MEGEngine::Vec2(0.0f,  0.0f)}

};

GLuint lightIndices[] =
{
	// top
	0, 1, 2,
	2, 3, 0,

	// front
	4, 5, 6,
	6, 7, 4,

	// right
	8, 9, 10,
	10, 11, 8,

	// back
	12, 13, 14,
	14, 15, 12,

	// left
	16, 17, 18,
	18, 19, 16,

	// bottom
	20, 21, 22,
	22, 23, 20
};

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
		Vec3 lightPos = Vec3(0.0f, 0.0f, 0.0f);

		Shader objectShader((g_resourcesDir + "/shaders/default.vert").c_str(), (g_resourcesDir + "/shaders/default.frag").c_str());
		objectShader.activate();
		objectShader.setUniform("lightColour", lightColour);
		objectShader.setUniform("lightPos", lightPos);

		std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
		std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
		std::vector<Texture> tex {Texture("", "diffuse", 0)};
		Mesh light(lightVerts, lightInd, tex);

		Shader lightShader((g_resourcesDir + "/shaders/light.vert").c_str(), (g_resourcesDir + "/shaders/light.frag").c_str());
		lightShader.activate();
		lightShader.setUniform("lightColour", lightColour);
		lightShader.setUniform("translation", lightPos);


		// glm::vec3 cameraPos = glm::vec3(-5.0f, 7.0f, 5.0f);
		Vec3 cameraPos = Vec3(0.0f, 0.0f, -10.0f);
	    Camera camera(g_windowWidth, g_windowHeight, cameraPos);
		// camera.orientation = glm::rotate(camera.orientation, glm::radians(-45.0f), camera.up); // left-right rotation
		camera.orientation = Private::fromGlmVec3(glm::rotate(Private::toGlmVec3(camera.orientation), glm::radians(-30.0f), glm::normalize(glm::cross(Private::toGlmVec3(camera.orientation), Private::toGlmVec3(camera.up))))); // up-down rotation

		Model sword((g_resourcesDir + "/models/sword/sword.gltf").c_str());
		sword.transform = Vec3(-10.0f, -10.0f, 4.0f);
		sword.orientation = Quat(0, 0, 0.707, 0.707);
		sword.scale = 0.2f;

		auto lastTime = clock::now();

	    while (!glfwWindowShouldClose(window)) {

	        // set background colour
	        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);

	        // clean back buffer and depth buffer
	        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	    	sword.transform += Vec3(1, 0, 0) * deltaTime();

	        // camera.processInputs(window, deltaTime());
    		camera.updateMatrix(70.0f, 0.1f, 1000.0f);

    		sword.draw(objectShader, camera);
    		light.draw(lightShader, camera, Mat4(1.0), lightPos);

	        // bring buffer to the front
	        glfwSwapBuffers(window);

	        // poll for events, otherwise program doesn't respond
	        glfwPollEvents();

	        // Limit FPS and set deltaTime
	    	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	    	setDeltaTime(lastTime);
	    }

	    // cleanup
		objectShader.del();
		// lightShader.del();

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