/*
	Application
*/
#include "AppProgram/Program/AppControl/App.h"
using namespace Application;

/*
	Scene
*/
#include "Scene.h"
using namespace SceneControl;

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