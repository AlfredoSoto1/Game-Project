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
#include "Framework/AppManager/Application.h"
#include "Framework/AppManager/AppComponent.h"
using namespace FrameworkEngine;
/*
	Scene
*/
#include "Framework/SceneManager/Scene.h"
#include "Framework/SceneManager/SceneManager.h"
using namespace SceneControl;

SceneManager::SceneManager(Application* _reference)
	: AppComponent(_reference)
{
	frames = 0;
	lastTime = 0;
	lastRefresh = 0;
	timeDifference = 0;
	lastTimeDifference = 0;

	hasChangedScene = false;

	currentScene = nullptr;

	setTargetFPS(0);
}

SceneManager::~SceneManager() {
	
}

void SceneManager::init() {
	currentScene->setApplication(getAppRef());
	currentScene->init();
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
	if (targetFrames > 0) {
		while (glfwGetTime() < lastTime + 1.0 / targetFrames);
		lastTime += 1.0 / targetFrames;
	}
}

short SceneManager::getTargetFPS() {
	return targetFrames;
}

void SceneManager::setTargetFPS(short _FPS) {
	targetFrames = _FPS;
}

void SceneManager::addScene(Scene* _scene) {
	this->currentScene = _scene;
}
