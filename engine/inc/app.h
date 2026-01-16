//
// Created by Will on 03/01/2026.
//

#ifndef WINDOW_H
#define WINDOW_H

namespace Engine {
	extern const char* appWindowName;
	extern int appDefaultWindowX;
	extern int appDefaultWindowY;

	class App {
	public:
		void Run();

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};

	App* CreateApp();

} // Engine

#endif //WINDOW_H