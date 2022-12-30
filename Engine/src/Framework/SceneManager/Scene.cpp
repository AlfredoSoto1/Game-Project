/*
	Application
*/
#include "Framework/AppManager/Application.h"
using namespace FrameworkEngine;

/*
	Scene
*/
#include "Scene.h"
using namespace SceneControl;

Scene::Scene() {
	application = nullptr;
}

Scene::~Scene() {

}

void Scene::setApplication(FrameworkEngine::Application* _reference) {
	application = _reference;
}

Application& Scene::getApplication() {
	return *application;
}