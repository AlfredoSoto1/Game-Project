/*
	Application
*/
#include "Application/App.h"
using namespace Application;

/*
	Scene
*/
#include "SceneUtils/Scene.h"
using namespace SceneUtils;

Scene::Scene() {
	app = nullptr;
}

Scene::~Scene() {

}

void Scene::setApplication(Application::App* _app) {
	app = _app;
}

Application::App& Scene::getApp() {
	return *app;
}