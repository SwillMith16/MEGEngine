#include "application.h"

class ExampleGame : public MEGEngine::Application {
public:
	using Application::Application;

protected:
	void onInit() override {
		// once at start
	}

	void onUpdate(float dt) override {
		// once per frame
	}
};

int main() {
	MEGEngine::ApplicationConfig appConfig;
	appConfig.windowTitle = "Test Game";

	ExampleGame game(appConfig);
	game.run();

    return 0;
}