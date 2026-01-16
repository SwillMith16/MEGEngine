//
// Created by Will on 08/12/2025.
//

#include "timer.h"
#include "settings.h"
#include "GLFW/glfw3.h"

float Timer::_deltaTime = 0;
float Timer::lastTime = 0;
float Timer::FPS = 0;

float Timer::deltaTime() { return _deltaTime; }

void Timer::processTime(TimerKey key) {
	float currentTime;
	// Limit FPS and set deltaTime
	do {
		currentTime = glfwGetTime();
		_deltaTime = currentTime - lastTime;
		FPS = 1 / _deltaTime;
	}
	while (FPS > Settings::maxFPS && Settings::maxFPS != 0);
	lastTime = currentTime;
}

