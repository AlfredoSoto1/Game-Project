#include "Stage.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings/WindowSettings.h"

using namespace Settings;
using namespace StageUtils;

Stage::Stage() {
	frames = 0;
	lastTime = 0;
	lastRefresh = 0;
	timeDifference = 0;
	lastTimeDifference = 0;

	windowSettings = nullptr;
}

Stage::~Stage() {

}

void Stage::addScene(const Scene& _scene) {
	scenes.emplace_back(_scene);
}

void Stage::calcFramerate() {
	//Calculates FPS
	frames++;
	if (glfwGetTime() * 1000.0 > lastRefresh + 1000.0) {
		std::cout << "FPS: " << frames << ", " << glfwGetTime() << std::endl;
		frames = 0;
		lastRefresh = glfwGetTime() * 1000.0;
	}

	double currentTime = glfwGetTime();
	timeDifference = (currentTime - lastTimeDifference);
	lastTimeDifference = currentTime;
}

void Stage::limitFramerate() {
	//Current thread sleeps here to get targeted FPS
	if (!windowSettings->isVSyncEnabled()) {
		while (glfwGetTime() < lastTime + 1.0 / windowSettings->getTargetFPS());
		lastTime += 1.0 / windowSettings->getTargetFPS();
	}
}

void Stage::init(WindowSettings* _windowSettings) {
	this->windowSettings = _windowSettings;

	//Here load everything before loop
}

void Stage::render() {
	
}

void Stage::postRender() {
	limitFramerate();
	calcFramerate();
}

void Stage::update() {
	
}

void Stage::dispose() {
	//Here delete everything after exiting loop	

}
