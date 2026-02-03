#include <memory>

#include "MEGEngine.h"
#include "MEGEngine/math/quat.h"
#include "MEGEngine/utils/log.h"

#include "CustomEvents.h"

class ExampleGame : public MEGEngine::Application {
public:
	using Application::Application;

protected:
	void onInit() override {
		// once at start
		MEGEngine::InputManager::bindInputLayout<MEGEngine::WASDLayout>();
		scene().camera().createEventListener<MEGEngine::MoveForwardEventListener, MEGEngine::MoveForwardEvent>();

		scene().camera().transform().setPosition({0, 0, -10});

		auto& light = scene().createEntity<MEGEngine::Light>();
		light.setColour({1.0, 1.0, 1.0, 1.0});
		MEGEngine::modelLoader.loadModelFromData(light, MEGEngine::Cube::vertices(), MEGEngine::Cube::indices());
		light.meshRenderer()->setMaterial(std::make_shared<MEGEngine::Material>(MEGEngine::ShaderManager::getShader("light")));

		auto& sword = scene().createEntity<MEGEngine::Entity>();
		MEGEngine::modelLoader.loadModelFromFile(sword, (MEGEngine::settings.general().modelDirectory + "/sword/sword.gltf").c_str());
		sword.transform().setPosition(MEGEngine::Vec3(-5, -5, 10));
		sword.transform().setOrientation(MEGEngine::Quat(0, 0, 0, 1));
		sword.transform().setScale(0.2);

	}

	void onUpdate() override {
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