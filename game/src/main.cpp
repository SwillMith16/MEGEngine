#include <memory>

#include "application.h"
#include "scene.h"
#include "entity.h"
#include "material.h"
#include "shader.h"
#include "model_loader.h"
#include "primitive_shapes.h"
#include "shader_manager.h"
#include "texture.h"

#include "math/quat.h"

class ExampleGame : public MEGEngine::Application {
public:
	using Application::Application;

protected:
	void onInit() override {
		// once at start
		MEGEngine::Vec4 lightColour = MEGEngine::Vec4(1.0f, 1.0f, 1.0f, 1.0f);

		MEGEngine::Entity& light = scene().createEntity();
		MEGEngine::modelLoader.loadModelFromData(light, MEGEngine::Cube::vertices(), MEGEngine::Cube::indices());
		std::vector<MEGEngine::Texture> tex {MEGEngine::Texture("", "diffuse", 0)};
		light.meshRenderer()->setMaterial(std::make_shared<MEGEngine::Material>(MEGEngine::ShaderManager::getShader("light")));
		light.meshRenderer()->material()->setTextureList(tex);
		if (light.meshRenderer()->material()->shader()) {
			light.meshRenderer()->material()->shader()->activate();
			light.meshRenderer()->material()->shader()->setUniform("lightColour", lightColour);
			light.meshRenderer()->material()->shader()->setUniform("translation", light.transform().position());
		}


		MEGEngine::Entity& sword = scene().createEntity();
		MEGEngine::modelLoader.loadModelFromFile(sword, (MEGEngine::settings.general().modelDirectory + "/sword/sword.gltf").c_str());
		sword.transform().setPosition(MEGEngine::Vec3(-5, -5, 10));
		sword.transform().setRotation(MEGEngine::Quat(0, 0, 0.707, 0.707));
		sword.transform().setScale(0.5);
		if (sword.meshRenderer()->material()->shader()) {
			sword.meshRenderer()->material()->shader()->activate();
			sword.meshRenderer()->material()->shader()->setUniform("lightColour", lightColour);
			sword.meshRenderer()->material()->shader()->setUniform("lightPos", light.transform().position());
		}
	}

	void onUpdate(float dt) override {
		// once per frame
	}
};

int main() {
	MEGEngine::ApplicationConfig appConfig;
	appConfig = {
		.windowTitle = "Test Game",
		.width = 1280,
		.height = 720
	};

	ExampleGame game(appConfig);
	game.run();

    return 0;
}