#include <memory>

#include "MEGEngine.h"
#include "MEGEngine/event_manager.h"
#include "MEGEngine/events.h"
#include "MEGEngine/math/quat.h"
#include "MEGEngine/utils/log.h"

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

		// MEGEngine::EventManager::trigger(std::make_shared<MEGEngine::NewEntityEvent>());

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


		scene().camera().transform().setPosition({0, 0, 10}); // TODO: z-axis of camera is opposite to everything else
	}

	void onUpdate(float dt) override {
		// once per frame
		MEGEngine::EventManager::processEvents();
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