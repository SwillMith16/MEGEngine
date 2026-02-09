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
		MEGEngine::Engine::instance().setInputSystem(&inputSystem); // for access throughout the application
		inputSystem.init();
		MEGEngine::KeyboardDevice keyboard(&window());
		inputSystem.manager().addDevice(std::make_unique<MEGEngine::KeyboardDevice>(keyboard));
		auto& move = inputSystem.createAction("Move", MEGEngine::InputAction::Type::FLOAT);
		auto gameplay = inputSystem.createContext();
		inputSystem.bind(*gameplay, move, MEGEngine::InputSource{MEGEngine::InputSource::Type::KEY, MEGEngine::KeyCode::W}, +1);
		inputSystem.pushContext(gameplay);
		inputSystem.subscribe(move, [](const MEGEngine::ActionState& s) {
			if (s.ongoing)
				MEGEngine::Log(LogLevel::DBG, "Move: %f", s.value.asFloat());
		});

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