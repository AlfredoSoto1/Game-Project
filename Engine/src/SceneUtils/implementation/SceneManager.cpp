/*
	GLFW & GLEW & External
*/
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;
/*
	Application
*/
#include "Application/App.h"
#include "Application/AppComponent.h"

using namespace Application;
/*
	Display
*/
#include "Display/Window.h"

using namespace Display;
/*
	Settings
*/
#include "Settings/WindowSettings.h"

using namespace Settings;
/*
	Scene
*/
#include "SceneUtils/Scene.h"
#include "SceneUtils/SceneManager.h"

using namespace SceneUtils;

SceneManager::SceneManager()
	: AppComponent()
{
	frames = 0;
	lastTime = 0;
	lastRefresh = 0;
	timeDifference = 0;
	lastTimeDifference = 0;

	hasChangedScene = false;

	currentScene = nullptr;
}

SceneManager::~SceneManager() {
	
}

void SceneManager::init() {
	
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
	if (!getAppRef()->window->getWindowSettings().isVSyncEnabled()) {
		while (glfwGetTime() < lastTime + 1.0 / getAppRef()->window->getWindowSettings().getTargetFPS());
		lastTime += 1.0 / getAppRef()->window->getWindowSettings().getTargetFPS();
	}
}

void SceneManager::addScene(Scene* _scene) {
	this->currentScene = _scene;
}
