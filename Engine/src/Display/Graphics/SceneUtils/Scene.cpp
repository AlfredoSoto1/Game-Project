#include "Scene.h"

#include "SceneManager.h"

using namespace SceneUtils;

Scene::Scene() {
	
}

Scene::~Scene() {

}

SceneManager& Scene::getSceneManager() {
	return *sceneManager;
}

void Scene::setSceneManager(SceneManager* _sceneManager) {
	this->sceneManager = _sceneManager;
}

