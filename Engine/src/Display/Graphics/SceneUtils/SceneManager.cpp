#include "SceneManager.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings/MouseSettings.h"
#include "Settings/WindowSettings.h"

#include "Scene.h"

using namespace std;
using namespace Settings;
using namespace SceneUtils;

SceneManager::SceneManager() {
	frames = 0;
	lastTime = 0;
	lastRefresh = 0;
	timeDifference = 0;
	lastTimeDifference = 0;

	hasChangedScene = false;

	currentScene = nullptr;
	mouseSettings = nullptr;
	windowSettings = nullptr;
}

SceneManager::~SceneManager() {

}

void SceneManager::init() {
	currentScene->setSceneManager(this);
}

void SceneManager::draw() {
	currentScene->render();
}

void SceneManager::afterDraw() {
	limitFramerate();
	calcFramerate();
}

void SceneManager::update() {
	currentScene->update();
}

void SceneManager::dispose() {
	currentScene->dispose();
}

void SceneManager::calcFramerate() {
	//Calculates FPS
	frames++;
	if (glfwGetTime() * 1000.0 > lastRefresh + 1000.0) {
		cout << "FPS: " << frames << ", " << glfwGetTime() << endl;
		frames = 0;
		lastRefresh = glfwGetTime() * 1000.0;
	}

	double currentTime = glfwGetTime();
	timeDifference = (currentTime - lastTimeDifference);
	lastTimeDifference = currentTime;
}

void SceneManager::limitFramerate() {
	//Current thread sleeps here to get targeted FPS
	if (!windowSettings->isVSyncEnabled()) {
		while (glfwGetTime() < lastTime + 1.0 / windowSettings->getTargetFPS());
		lastTime += 1.0 / windowSettings->getTargetFPS();
	}
}

Settings::MouseSettings& SceneManager::getMouseSettings() {
	return *mouseSettings;
}

Settings::WindowSettings& SceneManager::getWindowSettings() {
	return *windowSettings;
}


void SceneManager::loadMouseSettings(Settings::MouseSettings* _mouseSettings) {
	this->mouseSettings = _mouseSettings;
}

void SceneManager::loadWindowSettings(Settings::WindowSettings* _windowSettings) {
	this->windowSettings = _windowSettings;
}

void SceneManager::addScene(Scene* _scene) {
	this->currentScene = _scene;
}