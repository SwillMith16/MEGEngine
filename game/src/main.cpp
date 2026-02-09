#include <memory>

#include "MEGEngine.h"
#include "MEGEngine/math/quat.h"
#include "MEGEngine/utils/log.h"

#include "CustomEvents.h"

class ExampleGame : public MEGEngine::Application {
public:
	using Application::Application;
	MEGEngine::InputSystem inputSystem;

protected:
	void onInit() override {
		// once at start
		inputSystem.init();
		MEGEngine::Engine::instance().setInputSystem(&inputSystem); // for access throughout the application
		MEGEngine::KeyboardDevice keyboard(&window());
		inputSystem.manager().addDevice(std::make_unique<MEGEngine::KeyboardDevice>(keyboard));
		// TODO: Have a single move action that takes a Vec2 or Vec3?
		auto& moveFwd = inputSystem.createAction("MoveForward", MEGEngine::InputAction::Type::FLOAT);
		auto& moveBwd = inputSystem.createAction("MoveBackward", MEGEngine::InputAction::Type::FLOAT);
		auto& moveRgt = inputSystem.createAction("MoveRight", MEGEngine::InputAction::Type::FLOAT);
		auto& moveLft = inputSystem.createAction("MoveLeft", MEGEngine::InputAction::Type::FLOAT);
		auto gameplay = inputSystem.createContext();
		inputSystem.bind(*gameplay, moveFwd, MEGEngine::InputSource{MEGEngine::InputSource::Type::KEY, MEGEngine::KeyCode::W}, +1);
		inputSystem.bind(*gameplay, moveLft, MEGEngine::InputSource{MEGEngine::InputSource::Type::KEY, MEGEngine::KeyCode::A}, -1);
		inputSystem.bind(*gameplay, moveBwd, MEGEngine::InputSource{MEGEngine::InputSource::Type::KEY, MEGEngine::KeyCode::S}, -1);
		inputSystem.bind(*gameplay, moveRgt, MEGEngine::InputSource{MEGEngine::InputSource::Type::KEY, MEGEngine::KeyCode::D}, +1);
		inputSystem.pushContext(gameplay);

		scene().camera().init();

		scene().camera().transform().setPosition({0, 0, -10});

		auto& light = scene().createEntity<MEGEngine::Light>();
		light.setColour({1.0, 1.0, 1.0, 1.0});
		MEGEngine::modelLoader.loadModelFromData(light, MEGEngine::Cube::vertices(), MEGEngine::Cube::indices());
		light.meshRenderer()->setMaterial(std::make_shared<MEGEngine::Material>(MEGEngine::ShaderManager::getShader("light")));
		light.meshRenderer()->material()->setColour({1.0, 1.0, 1.0, 1.0});

		auto& sword = scene().createEntity<MEGEngine::Entity>();
		MEGEngine::modelLoader.loadModelFromFile(sword, (MEGEngine::settings.general().modelDirectory + "/sword/sword.gltf").c_str());
		sword.transform().setPosition(MEGEngine::Vec3(-5, -5, 10));
		sword.transform().setOrientation(MEGEngine::Quat(0, 0, 0, 1));
		sword.transform().setScale(0.2);

		auto& floor = scene().createEntity<MEGEngine::Entity>();
		MEGEngine::modelLoader.loadModelFromData(floor, MEGEngine::Cube::vertices(), MEGEngine::Cube::indices());
		floor.meshRenderer()->setMaterial(std::make_shared<MEGEngine::Material>());
		floor.meshRenderer()->material()->setColour({1.0, 1.0, 1.0, 1.0});
		floor.transform().setPosition(MEGEngine::Vec3(0, -30, 0));
		floor.transform().setScale(MEGEngine::Vec3(100, 0.1, 100));

	}

	void onUpdate() override {
		// once per frame
		MEGEngine::EventManager::processEvents();
		inputSystem.update();
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