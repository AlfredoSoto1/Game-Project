#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"
using namespace Uranium;

Scene::Scene(const std::string& _name)
	: sceneName(_name), nextScene("Default")
{
	isPaused = false;
	changeScene_requested = false;

	frames = 0;
	lastTime = 0;
	lastRefresh = 0;
	targetFrames = 0;
	timeDifference = 0;
	lastTimeDifference = 0;
}

Scene::~Scene() {

}

bool Scene::hasToChangeScene() {
	return changeScene_requested;
}

short Scene::unlimitedFramerate() {
	return 0;
}

std::string& Scene::getNextScene() {
	return nextScene;
}

std::string& Scene::getName() {
	return sceneName;
}

void Scene::changeScene(bool _changeScene_Requested) {
	changeScene_requested = _changeScene_Requested;
}

void Scene::setNextScene(const std::string& _nextScene) {
	nextScene = _nextScene;
}

void Scene::setTargetFPS(short _FPS) {
	targetFrames = _FPS;
}

bool Scene::isWaiting() {
	return isPaused;
}

void Scene::wait() {
	isPaused = true;
}

void Scene::resume() {
	isPaused = false;
}

void Scene::reset() {
	changeScene_requested = false;
}

void Scene::calibrateFramerate() {
	//Current thread sleeps here to get targeted FPS
	if (targetFrames > unlimitedFramerate()) {
		while (glfwGetTime() < lastTime + 1.0 / targetFrames);
		lastTime += 1.0 / targetFrames;
	}
}

void Scene::postDraw() {
	calibrateFramerate();
	
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

